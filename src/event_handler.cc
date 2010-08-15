#include "event_handler.h"


void event_handler::on_event(SDL_Event *e) {
  if (filter_event(e) == false) {
  if (e) {
    switch (e->type) {
    case SDL_KEYDOWN: {
      on_key_down(e->key.keysym.sym, e->key.keysym.mod, e->key.keysym.unicode);
      break;
    }
    
    case SDL_KEYUP: {
      SDL_keysym k = e->key.keysym;
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
      int x = e->button.x; // declared from mousebutton down
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

    case SDL_VIDEORESIZE: {
      on_resize(e->resize.w, e->resize.h);
      break;
    }
    
    case SDL_ACTIVEEVENT: {
      if (e->active.state == SDL_APPMOUSEFOCUS) {
        if (e->active.gain) on_mouse_focus();
        else on_mouse_blur();
      
      } else if (e->active.state == SDL_APPINPUTFOCUS) {
        if (e->active.gain) on_input_focus();
        else on_input_blur();
      
      } else if (e->active.state == SDL_APPACTIVE) {
        if (e->active.gain) on_restore();
        else on_minimize();
      }
      break;
    }

    case SDL_VIDEOEXPOSE: {
      on_expose();
      break;
    }

    case SDL_USEREVENT: {
      on_user(e->user.type, e->user.code, e->user.data1, e->user.data2);
      break;
    }

    default:
      break;
    }
  }
  }
}


bool event_handler::filter_event(SDL_Event *e) {
  return false;
}
