#include "ui/control.h"

control *control::main_control = NULL;
control *control::keyboard_focus = NULL;
control *control::mouse_focus = NULL;
control *control::mouse_hover = NULL;
control_list control::update_list;
control_list control::close_list;
TTF_Font *control::font = NULL;

int control::msg = 0;


color control::default_fg_color = color(220,220,220);
color control::default_bg_color = color(32,32,32);
color control::default_frame_color = color(220,220,220);
color control::default_focus_color = color(255,255,255);


/** Contruct a control from a canvas. */
control::control(canvas *c) {
  if (!c) {
    fprintf(stderr, "control::control(canvas*): got null pointer");
    exit(1);
  }
  parent = NULL;
  dimensions = rect(0,0,c->get_w(),c->get_h());
  id = 0;
  this->c = c;
  hidden = false;
  control::main_control = this;
}


/** Create a control.
 * @param parent parent control.
 * @param dimensions the position and the dimensions of the control.
 * @param id the id for the control. */
control::control(control *parent, rect dimensions, int id) {
  this->parent = parent;
  if (has_parent()) parent->add_child(this);
  else {
    if (control::get_main_control() == NULL) {
      control::main_control = this;
    } else {
      fprintf(stderr, "control::control(control*, rect, int): can only have one main_control");
      //exit(1);
    }
  }
  hidden = false;
  this->dimensions = dimensions;
  this->id = id;
  c = canvas::create_rgb_compatible(SDL_ANYFORMAT, 
                                    dimensions.get_w(), dimensions.get_h());
}


/** Default destructor. */
control::~control() {
  if (!is_main_control() && c) delete c;
  if(control::font) { 
    TTF_CloseFont(font); 
    font = NULL;
  }
  if(has_keyboard_focus()) control::set_keyboard_focus(NULL);
  if(has_mouse_focus()) control::set_mouse_focus(NULL);
  if(has_mouse_hover()) control::set_mouse_hover(NULL);
}


/** Redefine the parent of the control. */
void control::set_parent(control *parent) {
  if (this->parent) {
    this->parent->remove_child(this);
  }
  if (parent) {
    this->parent = parent;
    this->parent->add_child(this);
  } else {
    this->parent=NULL;
  }
}


/** Retreives the controls current parent. */
control *control::get_parent() {
  return parent;
}


/** Check if the control have a parent. */
bool control::has_parent() {
  if (parent) return true;
  else return false;
}


/** Add a child to this control.
 * @param child pointer to a cild-control. */
void control::add_child(control *child) {
  children.push_back(child);
}


/** Remove a child from this control.
 * @param child pointer to a child. */
void control::remove_child(control *child) {
  children.remove(child);
}


/** Set the id */
void control::set_id(int id) {
  this->id = id;
}


/** Get the id. */
int control::get_id() {
  return id;
}


/** Send a message to parent control. 
 * @param msg the message.
 * @param param1-4 the data to send with the message.  
 * @return true if the message was handeled upstream, else false. */
bool control::send_message(int msg, void *param1, void *param2, void *param3, void *param4) {
  if (has_parent()) return get_parent()->on_message(msg, param1, param2, param3, param4);
  else return false;
}


/** Handle a message.
 * @param msg the message.
 * @param param1-4 the data received with the message.  
 * @return true if the message was handeled. */
bool control::on_message(msgid id, void *param1, void *param2, void *param3, void *param4) {
  if (parent) {
    return parent->on_message(id, param1, param2, param3, param4);
  }
  else return false;
}


/** Bring this control to front. */
void control::bring_to_front() {
  control::update_list.push_back(this);
}


/** Close this control.
 * You will have to call update() for the 
 * control to be actually closed.
 * @see update() */
void control::close() {
  if (!is_main_control()) {
    control::close_list.push_back(this);
  }

  if (children.empty()==false) {
    control_list_iter it;
    for (it=children.begin(); it!=children.end(); it++) {
      (*it)->close();
    }
    children.clear();
  }
}


/** Draw the control and all it's children, calling theirs on_draw().
 * @see on_draw() */
void control::draw() {
  if (hidden) return;
  on_draw();

  /* draw all children */
  if (children.empty()==false) {
    for (control_list_iter it=children.begin(); it!=children.end(); it++) {
      (*it)->draw();
    }
  }
}


/** Called by draw(), override when inheriting. */
void control::on_draw() { }


/** Update all control. 
 * Check the update-list and the close-list. */
void control::update() {
  control_list_iter it;

  /* update all in update_list */
  if (control::update_list.empty() == false) {
    for (it=control::update_list.begin(); it!=control::update_list.end(); it++) {
      (*it)->draw();
    }
    control::update_list.clear();
  }


  /* delete all in close-list */
  if (control::close_list.empty() == false) {
    for (it=control::close_list.begin(); it!=control::close_list.end(); it++) {
      delete (*it);
    }
    control::close_list.clear();
  }
}


/** Redraw all controls. */
void control::redraw() {
  if (control::main_control==NULL) {
    fprintf(stderr, "control::redraw: main_control == NULL");
    exit(1);
  }

  control_list_iter it;
  for (it=control::main_control->children.begin(); it!=control::main_control->children.end(); it++) {
    (*it)->draw();
  }
}


/** Parse event.
 * @param e event to parse. */
bool control::on_event(SDL_Event *e) {
  switch(e->type) {
  case SDL_KEYDOWN: {
    on_key_down(e->key.keysym.sym, e->key.keysym.mod, e->key.keysym.unicode);
    break;
  }

  case SDL_KEYUP: {
    on_key_up(e->key.keysym.sym, e->key.keysym.mod, e->key.keysym.unicode);
    break;
  }

  case SDL_MOUSEMOTION: {
    on_mouse_move(e->motion.x, e->motion.y, e->motion.xrel, e->motion.yrel,
                  e->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT),
                  e->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT),
                  e->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE));
    break;
  }

  case SDL_MOUSEBUTTONDOWN: {
    int x = e->button.x;
    int y = e->button.y;
    if (e->button.button == SDL_BUTTON_LEFT) {
      on_lbutton_down(x, y);
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
      on_rbutton_down(x, y);
    } else if (e->button.button == SDL_BUTTON_MIDDLE) {
      on_mbutton_down(x, y);
    }
    break;
  }

  case SDL_MOUSEBUTTONUP: {
    int x = e->button.x;
    int y = e->button.y;
    if (e->button.button == SDL_BUTTON_LEFT) {
      on_lbutton_up(x, y);
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
      on_rbutton_up(x, y);
    } else if (e->button.button == SDL_BUTTON_MIDDLE) {
      on_mbutton_up(x, y);
    }
    break;
  }

  default:
      break;
  }
  return true;
}


/** Filter the event for faster dispatching.
 * This will filter the event and dispatch mouse and keyboard
 * events directly to the focused control - avoiding the normal
 * parent->child process.
 * @param e the event to filter.
 * @return true if the event was filtered, else false. */
bool control::filter_event(SDL_Event *e) {
  if (!control::get_main_control()) {
    return false;
  }
  
  rect dimensions = control::get_main_control()->get_dimensions();

  switch (e->type) {
  case SDL_MOUSEMOTION: {
    // convert coord to local
    point pos(e->motion.x, e->motion.y);
    pos -= dimensions;

    // check if within main control
    if (control::get_main_control()->coord_within(pos)) {

      // cord within child?
      control *c;
      if ((c=control::get_main_control()->coord_within_child(pos)) != NULL) {
        // yes
        control::set_mouse_hover(c);
      } else {
        //no
        control::set_mouse_hover(control::get_main_control());
      }
      // call event handler
      control::get_mouse_hover()->on_mouse_move(pos.get_x(), pos.get_y(), e->motion.xrel, e->motion.yrel,
                                                e->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT),
                                                e->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT),
                                                e->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE));
    } else {
      // mouse outside main_control
      control::set_mouse_hover(NULL);
      return false;
    }
    return true;
  }

  case SDL_MOUSEBUTTONDOWN: {
    control *ctrl;

    // hovering a control?
    if ((ctrl=control::get_mouse_hover()) == NULL) {
      control::set_mouse_focus(NULL);
      return false;
    }

    // always clear keyboard focus on a click
    control::set_keyboard_focus(NULL);

    // focus on it
    control::set_mouse_focus(ctrl);

    // convert to local coord
    point pos(e->button.x, e->button.y);
    pos -= dimensions;

    // call event handler
    if (e->button.button == SDL_BUTTON_LEFT) {
      ctrl->on_lbutton_down(pos.get_x(), pos.get_y());
    } else if (e->button.button == SDL_BUTTON_MIDDLE) {
      ctrl->on_mbutton_down(pos.get_x(), pos.get_y());
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
      ctrl->on_rbutton_down(pos.get_x(), pos.get_y());
    }

    return true;
  }

  case SDL_MOUSEBUTTONUP: {
    control *ctrl;

    // have clicked down on a control? (have focus)
    if ((ctrl=control::get_mouse_focus()) == NULL) {

      return false;
    }

    // convert to local coord
    point pos(e->button.x, e->button.y);
    pos -= (point)dimensions;


    // call event handler
    if (e->button.button == SDL_BUTTON_LEFT) {
      ctrl->on_lbutton_up(pos.get_x(), pos.get_y());
    } else if (e->button.button == SDL_BUTTON_MIDDLE) {
      ctrl->on_mbutton_up(pos.get_x(), pos.get_y());
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
      ctrl->on_rbutton_up(pos.get_x(), pos.get_y());
    }    
    return true;
  }

  case SDL_KEYDOWN: {
    if (control::get_keyboard_focus()!=NULL)
      return control::get_keyboard_focus()->on_key_down(e->key.keysym.sym, e->key.keysym.mod, e->key.keysym.unicode);
  }

  case SDL_KEYUP: {
    if (control::get_keyboard_focus()!=NULL)
      return control::get_keyboard_focus()->on_key_up(e->key.keysym.sym, e->key.keysym.mod, e->key.keysym.unicode);
  }

  default:
    break;
  }
  return false;
}


/** Get the position of the control. */
point control::get_position() {
  return dimensions;
}


/** Set the position of the control. */
void control::set_position(point position) {
  dimensions.place(position);
}


/** See if a point is within the control.\ The coordinate must be relative to the main_control.
 * @return true if pos within else false. */
bool control::coord_within(point pos) {
  if (is_main_control()) {
    // convert to absolute coords
    pos += dimensions;
  }

  return (get_left() <= pos.get_x() && pos.get_x() <= get_right() &&
          get_top() <= pos.get_y() && pos.get_y() <= get_bottom());
}


/** See if a point is within a child of the control 
 * @return pointer to the child that's at the pos. */
control *control::coord_within_child(point pos) {
  if (children.empty()) return NULL;

  control *ctrl = NULL;

  // check if within a child or sub-child
  for (control_list_iter it=children.begin(); it!=children.end(); it++) {
    if ((*it)->coord_within(pos) || (ctrl=(*it)->coord_within_child(pos))!=NULL ) {
      return ctrl ? ctrl : (*it);
    }
  }
  return NULL;
}
