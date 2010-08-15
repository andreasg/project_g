
#include "ui/label.h"


label::label(control *parent, rect dimensions, std::string text, int id, 
             color fg_color, color bg_color) : control(parent, dimensions, id) {
  this->text = text;
  this->fg_color = fg_color;
  this->bg_color = bg_color;
  text_canvas = new canvas(TTF_RenderText_Blended(control::font, text.c_str(), fg_color));
}


void label::set_text(std::string text) {
  this->text = text;
  if (text_canvas) delete text_canvas;
  text_canvas = new canvas(TTF_RenderText_Blended(control::font, text.c_str(), fg_color));
}


void label::on_draw() {
  if (text_canvas == NULL) return;

  rect clip_rect = get_canvas()->get_clip_rect();
  get_canvas()->fill_rect(clip_rect, bg_color);

  clip_rect.shrink(1,1);
  rect text_clip_rect = text_canvas->get_clip_rect();
  get_canvas()->blit(clip_rect, *text_canvas, text_clip_rect);

  if (has_parent()) {
    clip_rect.shrink(-1, -1);
    get_parent()->get_canvas()->blit(dimensions, *get_canvas(), clip_rect);
  }
}
