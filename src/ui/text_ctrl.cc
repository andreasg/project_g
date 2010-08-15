#include "ui/text_ctrl.h"


msgid text_ctrl::msgid_text_ctrl_text = control::next_msgid();
text_ctrl::carret_timer *text_ctrl::blinker = NULL;


text_ctrl::text_ctrl(control *parent, rect dimensions, int id) : control(parent, dimensions, id) {
  text_canvas = NULL;
  set_position(dimensions);

  if (text_ctrl::blinker == NULL) {
    text_ctrl::blinker = new carret_timer();
    text_ctrl::blinker->set_interval(400);
    text_ctrl::blinker->start();
  }
}


void text_ctrl::on_draw() {
  rect clip_rect = get_canvas()->get_clip_rect();

  color frame;
  if (has_mouse_focus()) frame = control::default_focus_color;
  else frame = control::default_frame_color;

  get_canvas()->fill_rect(clip_rect, frame);

  clip_rect.shrink(1,1);
  get_canvas()->fill_rect(clip_rect, control::default_bg_color);

  clip_rect.shrink(2,2);

  if(text_canvas) {
    rect text_clip_rect = text_canvas->get_clip_rect();
    get_canvas()->blit(clip_rect, *text_canvas, text_clip_rect);
  }

  if (has_keyboard_focus() && text_ctrl::blinker->blink) {
    rect carret(2,4, 2, dimensions.get_h()-8);
    if (text_canvas) {
      carret.set_x(carret.get_x() + text_canvas->get_w() + 1);
    }
    get_canvas()->fill_rect(carret, control::default_fg_color);
  }

  clip_rect = get_canvas()->get_clip_rect();
  control::get_main_control()->get_canvas()->blit(dimensions, *get_canvas(), clip_rect);
}


bool text_ctrl::on_lbutton_down(int x, int y) {
  control::set_keyboard_focus(this);
  return true;
}


bool text_ctrl::on_key_down(SDLKey k, SDLMod m, Uint16 unicode) {
  if (!has_keyboard_focus()) return false;
  bool update = false;
  if ((SDLK_a <= k && k <= SDLK_z) || 
      (SDLK_0 <= k && k <= SDLK_9) ||
      k == SDLK_PERIOD ||
      k == '-' ||
      k==SDLK_SPACE) {
    text += (char)k;
    update = true;
  } else if (k == SDLK_BACKSPACE) {
    if (!text.empty()) {
      text.erase(text.end()-1);
      update = true;
    } 
  } else if (k == SDLK_RETURN) {
    // add send message with text here!
    send_message(text_ctrl::msgid_text_ctrl_text, (int*)get_id(), &text, NULL, NULL);
    control::set_keyboard_focus(NULL);
  } else if (k==SDLK_ESCAPE) {
    return false;
  }

  if (update) {
    if (text_canvas) {
      delete text_canvas;
      text_canvas = NULL;
    }
    if (text.empty()==false) {
      text_canvas = new canvas(TTF_RenderText_Blended(control::font, text.c_str(), control::default_fg_color));
    }
    return true;
  }
  return true;
}
