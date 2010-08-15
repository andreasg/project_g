#ifndef PG_MAIN_CANVAS_H
#define PG_MAIN_CANVAS_H

#include "canvas.h"
#include <SDL.h>


/** Use this to represent a screen. */
class main_canvas : public canvas {
public:
  main_canvas(int w, int h, int bpp, int flags);
  virtual ~main_canvas();
};


#endif
