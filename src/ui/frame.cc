#include "ui/frame.h"


frame::frame(control *parent, rect dimensions, int id, color bg_color, color frame_color) : control(parent, 
                                                                                                    dimensions, id) {
  this->bg_color = bg_color;
  this->frame_color = frame_color;
  set_position(dimensions);
}


frame::~frame() {}


void frame::on_draw() {
  canvas* c = get_canvas();
  rect clip_rect = c->get_clip_rect();
  c->fill_rect(clip_rect, frame_color);
  clip_rect.shrink(1,1);
  c->fill_rect(clip_rect, bg_color);
}


bool frame::on_event(SDL_Event *e) {
  switch (e->type) {

  case SDL_MOUSEMOTION: {
    return true;
  }

  case SDL_MOUSEBUTTONDOWN: {
    return true;
  }

  case SDL_MOUSEBUTTONUP: {
    return true;
  }
 

  default:
    break;
  }
  return false;
}

void frame::draw_ui(canvas *dest) {
  if (control::get_main_control() == NULL || dest == NULL) return;

  control* ui_ = control::get_main_control();
  ui_->draw();
  dest->blit((rect&)*ui_->get_dimensions(), *ui_->get_canvas(), (rect&)*ui_->get_canvas()->get_clip_rect());
}
