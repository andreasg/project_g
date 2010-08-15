
#include "ui/button.h"

#include <iostream>

msgid button::msgid_button_click = control::next_msgid();


/** Default constructor.
 * @param parent the parent control.
 * @param text the text on the button.
 * @param dimensions the size and position of the button relative to the parent.
 * @param id id of the button.
 * @param fg_col the text-color of the button.
 * @param bg_col the background color of the button. */
button::button(control *parent, std::string text, rect dimensions, int id,
               color fg_col, color bg_col) : control(parent, dimensions, id)  {
  fg_color = fg_col;
  bg_color = bg_col;
  this->text = text;
  text_canvas = new canvas(TTF_RenderText_Blended(control::font, 
                                                  text.c_str(), fg_color));

  set_position(dimensions);
}


button::~button() {
  if (text_canvas) delete text_canvas;
}


void button::set_text(std::string t) { 
  text = t; 
  if (text_canvas) {
    delete text_canvas;
  }
  text_canvas = new canvas(TTF_RenderText_Blended(control::font, text.c_str(), fg_color));
  std::cout << "new button text = " + t + "\n";
}


/* draws the button onto the parent's canvas 
   all the coordinates are relative to the parent */
void button::on_draw() {
  if (text_canvas!=NULL) {

    color frame;
    if (has_mouse_focus()) frame = control::default_focus_color;
    else frame = control::default_frame_color;

    rect clip_rect = get_canvas()->get_clip_rect();
    get_canvas()->fill_rect(clip_rect, frame);

    clip_rect.shrink(2,2);
    color bg = bg_color;
    if (has_mouse_hover()) bg += 30;
    get_canvas()->fill_rect(clip_rect, bg);

    clip_rect.shrink(2,2);    
    rect text_clip_rect = text_canvas->get_clip_rect();
    get_canvas()->blit(clip_rect, *text_canvas, text_clip_rect);
    
    if (has_parent()) {
      clip_rect = get_canvas()->get_clip_rect();
      get_parent()->get_canvas()->blit(dimensions, *get_canvas(), clip_rect);
    }
  }
}


bool button::on_lbutton_down(int x, int y) {
  bg_color -= 30;
  control::set_keyboard_focus(this);
  return true;
}

bool button::on_lbutton_up(int x, int y) {
  bg_color += 30;

  // msgid, id, this, parent, NULL
  if (coord_within(point(x,y)))
      send_message(button::msgid_button_click, (int*)get_id(), this, get_parent(), NULL);
  return true;
}

bool button::on_key_down(SDLKey k, SDLMod m, Uint16 unicode) {
  if (k==SDLK_RETURN) {
    send_message(button::msgid_button_click, (int*)get_id(), this, get_parent(), NULL);
    return true;
  }
  return false;
}
