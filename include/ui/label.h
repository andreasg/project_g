
#ifndef PG_UI_LABEL_H
#define PG_UI_LABEL_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "ui/control.h"

/** Label.
 * A label is a static component in a ui, it simply
 * displays a short line of text - a label. */
class label : public control {
public:

  label(control *parent, rect dimensions, std::string text, int id=0, 
        color fg_color=control::default_fg_color,
        color bg_color = control::default_bg_color);

  ~label() {if (text_canvas) delete text_canvas;}

  /** Set the text of the label. */
  void set_text(std::string text);

  /** Get the text of the label. */
  std::string get_text() {return text;}

  /** Draw the label. */
  virtual void on_draw();

private:
  std::string text;
  color fg_color;
  color bg_color;
  canvas *text_canvas;
};


#endif
