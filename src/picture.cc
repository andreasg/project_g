
#include "picture.h"


/** Create a picture.
 * @param src a canvas.
 * @param src_rect the clipping of the image.
 * @param offset the point to be the 'pivot' or 'center'
 *               of the image. */
picture::picture(canvas *src, rect src_rect, point offset) {
  c = src;
  this->src_rect = src_rect;
  dest_rect = src_rect;
  dest_rect -= offset;
  //  dest_rect.set(-offset.get_x(), -offset.get_y(), src_rect.get_w(), src_rect.get_h());
}


/** Default destructor. */
picture::~picture() {
  if (c) delete c;
}


/** Get the canvas. */
canvas *picture::get_canvas() {
  return c;
}


/** Set the canvas */
void picture::set_canvas(canvas *c) {
  this->c = c;
}


/** Blit the picture onto a canvas.
 * @param dst canvas to draw picture upon.
 * @param pos where to draw the picture. */
void picture::place(canvas *dst, point dst_point) {
  rect r = dest_rect;
  r += dst_point;
  dst->blit(r, *c, src_rect);
}
