
#ifndef PG_UI_FRAME_H
#define PG_UI_FRAME_H


#include "ui/control.h"

/**Frame.
   A frame will be your main_control - onto which
   other controls will be placed.
   You should only use one frame. */
class frame : public control {
public:
  frame(control *parent, rect dimensions, int id=0, color bg_color=control::default_bg_color,
        color frame_color=control::default_frame_color);
  virtual ~frame();

  virtual bool on_event(SDL_Event *e);

  /** Draw the frame. */
  virtual void on_draw();

  /** Blits the main_control to the destination canvas.
   * @param dest The canvas to blit the UI to.
   */
  static void draw_ui(canvas *dest);

protected:
  color bg_color;
  color frame_color;
};


#endif
