
#include "rect.h"


/** Default constructor. */
rect::rect() {
}


/** Create a rect */
rect::rect(int x, int y, int w, int h) {
  set(x, y, w, h);
}


/** Copy constructor. */
rect::rect(const rect &rec) {
  set(rec.r.x, rec.r.y, rec.r.w, rec.r.h);
}


/** Create a rect from a SDL_Rect */
rect::rect(SDL_Rect r) {
   set(r.x, r.y, r.w, r.h);
}


/** Create a new rect from a SDL_Rect*. */
rect::rect(SDL_Rect *r) {
  if (r) {
    set(r->x, r->y, r->w, r->h);
  }
}


/** Check if a point is within the rect.
 * @param p point. */
bool rect::within(point &p) {
  return (r.x <= p.get_x() && p.get_x() < r.w &&
          r.y <= p.get_y() && p.get_y() < r.h);
}


/** Check if a coord is withn the rect.
 * @param x coord.
 * @param y coord. */
bool rect::within(int x, int y) {
  return (r.x <= x && x < r.w &&
          r.y <= y && y < r.h);
}


/** Place the rect at a position.
 * @param p ponit to place the rect at. */
void rect::place(int x, int y) {
  r.x = x;
  r.y = y;
}


/** Place the rect at a coord.
 * @param x coord.
 * @param y coord. */
void rect::place(point &p) {
  r.x = p.get_x();
  r.y = p.get_y();
}


/** Move the rect, use a point to secify the offset.
 * @param p offset. */
void rect::offset(int x, int y) {
  r.x += x;
  r.y += y;
}


/** Move the rect the given coords. */
void rect::offset(point &delta) {
  r.x += delta.get_x();
  r.y += delta.get_y();
}


/** Shrink the rectangle. */
void rect::shrink(int dx, int dy) {
  r.x += dx;
  r.w -= (dx+dx);
  r.y += dy;
  r.h -= (dy+dy);
}


/** Check if the rectangle is empty 
 * @return true if empty, else false. */
bool rect::empty() {
  return (r.w==0 && r.h==0);
}


/** Set all the attributes of a rect. */
void rect::set(int x, int y, int w, int h) {
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
}


/** Move the rect. 
 * @note Size of the rect is not changed. */
rect &rect::operator+=(point p) {
  r.x += p.get_x();
  r.y += p.get_y();
  return *this;
}


/** Move the rect.
 * @note Size of the rect is not changed. */
rect &rect::operator-=(point p) {
  r.x -= p.get_x();
  r.y -= p.get_y();
  return *this;
}


/** Create a new rect at the old position + p */
rect rect::operator+(point p) {
  rect r_(r.x+p.get_x(), r.y+p.get_y(), r.w, r.h);
  return r_;
}


/** Create a new rect at the old position - p */
rect rect::operator-(point p) {
 rect r_(r.x-p.get_x(), r.y-p.get_y(), r.w, r.h);
  return r_;
}
