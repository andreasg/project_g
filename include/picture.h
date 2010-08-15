#ifndef PG_PICTURE_H
#define PG_PICTURE_H

#include <SDL.h>

#include "canvas.h"
#include "rect.h"
#include "point.h"


/** Abstraction of a canvas.
 *
 * A picture is a canvas with some additional information,
 * where the most important one is the offset. This allows
 * us to place any given point of the image at the coord 
 * we want - instead of the default top-left corner. We
 * can also clip the image to only draw parts of it. */
class picture {
public:
  picture(canvas *src, rect src_rect, point offset=point(0,0));
  virtual ~picture();

  canvas *get_canvas();

  void set_canvas(canvas *c);
  void place(canvas *dst, point dst_point);

  /** Get the source rectangle. */
  rect get_src_rect() {return src_rect;}
  /** Set the source rectangle. */
  void set_src_rect(rect r) {src_rect = r;}

  /** Get the destination rectangle. */
  rect get_dest_rect() {return dest_rect;}
  /** Set the destination rectangle. */
  void set_dest_rect(rect r) {dest_rect = r;}

private:
  canvas *c;
  rect src_rect;
  rect dest_rect;
};

#endif 
