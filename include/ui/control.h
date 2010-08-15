
#ifndef PG_CONTROL_H
#define PG_CONTROL_H

#include <list>

#include <SDL.h>
#include <SDL_ttf.h>

#include "point.h"
#include "rect.h"
#include "canvas.h"

class control;
typedef std::list<control*> control_list;
typedef std::list<control*>::iterator control_list_iter;



/** A abstract UI element. */
class control {
public:
  control(canvas *c);
  control(control *parent, rect dimensions, int id);
  virtual ~control();

  void set_parent(control *parent);
  control *get_parent();
  bool has_parent();

  void add_child(control *child);
  void remove_child(control *child);

  void set_id(int id);
  int get_id();

  bool send_message(int msg, void *param1=NULL, void *param2=NULL, 
                    void *param3=NULL, void *param4=NULL);
  virtual bool on_message(msgid id, void *param1, void *param2, void *param3, void *param4);

  void bring_to_front();

  void close();
  void draw();
  virtual void on_draw();
  static void update();
  static void redraw();

  /** Set if the control (and it's children) are to be hidden.
   * @param hidden True to hide, false to show. */
  void set_hidden(bool hidden) {this->hidden = hidden;}
  
  /** Get the hidden status for the control. */
  bool get_hidden() {return hidden;}

  virtual bool on_event(SDL_Event *e);
  
  /** Called when a key is pressed. */
  virtual bool on_key_down(SDLKey k, SDLMod m, Uint16 unicode) {return true;}
  /** Called when a key is released. */
  virtual bool on_key_up(SDLKey k, SDLMod m, Uint16 unicode) {return true;}
  /** Called when the mouse is moved. */
  virtual bool on_mouse_move(int x, int y, int relx, int rely, 
                             bool left, bool right, bool middle) {return true;}
  /** Called on left mousebutton down. */
  virtual bool on_lbutton_down(int x, int y) {return true;}
  /** Called on left mousebutton up. */
  virtual bool on_lbutton_up(int x, int y)   {return true;}
  /** Called on right mousebutton down. */
  virtual bool on_rbutton_up(int x, int y)   {return true;}
  /** Called on right mousebutton up. */
  virtual bool on_rbutton_down(int x, int y) {return true;}
  /** Called on middle mousebutton down. */
  virtual bool on_mbutton_up(int x, int y)   {return true;}
  /** Called on middle mousebutton up. */
  virtual bool on_mbutton_down(int x, int y) {return true;}

  static bool filter_event(SDL_Event *e);

  point get_position();
  void set_position(point p);


  bool coord_within(point pos);
  control *coord_within_child(point pos);

  /** Get the position and the dimensions of the control. */
  rect get_dimensions() {return dimensions;}


  /** Get the width of the control. */
  int get_w()      { return dimensions.get_w(); }

  /** Get the height of the control. */
  int get_h()      { return dimensions.get_h(); }

  /** Get the right edge. */
  int get_right()  { return c->get_w() + dimensions.get_x(); }
  /** Get the left edge. */
  int get_left()   { return dimensions.get_x(); }
  /** Get the top edge. */
  int get_top()    { return dimensions.get_y(); }
  /** Get the bottom edge. */
  int get_bottom() { return dimensions.get_y()+c->get_h(); }


  /** Get the canvas for the control. */
  canvas *get_canvas() { return c; }

  /** Get a poninter to the main control. */
  static control *get_main_control()            { return control::main_control; }
  
  /** Get a pointer to the control that has keyboard focus. */
  static control *get_keyboard_focus()          { return control::keyboard_focus; }
  /** Set a control to have keyboard focus. */
  static void set_keyboard_focus(control *ctrl) { control::keyboard_focus = ctrl; }

  /** Get a pointer to the control that has mouse focus. */
  static control *get_mouse_focus()             { return control::mouse_focus; }
  /** Set a control to have mouse focus. */
  static void set_mouse_focus(control *ctrl)    { control::mouse_focus = ctrl; }

    /** Get a pointer to the control that has the mouse over it. */
  static control *get_mouse_hover()             { return control::mouse_hover; }
  /** Set a control to have the mouse over it. */
  static void set_mouse_hover(control *ctrl)    { control::mouse_hover = ctrl; }

  /** Check if main control. */
  bool is_main_control()    { return (this == main_control); }

  /** Check if has keyboard focus. */
  bool has_keyboard_focus() { return (this == keyboard_focus); }

  /** Check if has mouse focus. */
  bool has_mouse_focus()    { return (this == mouse_focus); }

  /** Check if mouse is hovering this control. */
  bool has_mouse_hover()    { return (this == mouse_hover); }

  /** Font to use for all the control. */
  static TTF_Font *font;

  /** Default foreground color. */
  static color default_fg_color;
  /** Default background color. */
  static color default_bg_color;
  /** Default frame color. */
  static color default_frame_color;
  /** Default focus-frame color. */
  static color default_focus_color;

  static int next_msgid() {return msg++;}

protected:
  /** The position and size of the control. */
  rect dimensions;

  bool hidden;

private:
  control *parent;
  control_list children;
  canvas *c;

  int id;

  /* controls to be updated. */
  static control_list update_list;

  /* controls to be closed. */
  static control_list close_list;

  /* 'mother' control */
  static control *main_control;
  /* keyboard active control */
  static control *keyboard_focus;
  /* mouse active control */
  static control *mouse_focus;
  /* has mouse over it control */
  static control *mouse_hover;

  static int msg;
};



#endif
