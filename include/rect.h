#ifndef PG_RECT_H
#define PG_RECT_H


#include <SDL.h>

#include "point.h"

/** Abstraction of a SDL_Rect. */
class rect {
public:
  rect();
  rect(int x, int y, int w, int h);
  rect(const rect& rec);
  rect(SDL_Rect r);
  rect(SDL_Rect *r);

  virtual ~rect() {}

  bool within(point &p);
  bool within(int x, int y);
  void place(point &p);
  void place(int x, int y);
  void offset(point &p);
  void offset(int x, int y);
  void shrink(int dx, int dy);
  bool empty();

  /** Get the x-coord of the rect. */
  int get_x() {return r.x;}
  /** Get the y-coord of the rect. */
  int get_y() {return r.y;}
  /** Get the width of the rect. */
  int get_w() {return r.w;}
  /** Get the height of the rect. */
  int get_h() {return r.h;}
  /** Set the x position. */
  void set_x(int x) {r.x = x;}
  /** Set the y position. */
  void set_y(int y) {r.y = y;}
  /** Set the width of the rect. */
  void set_w(int w) {r.w = w;}
  /** Set the height of the rect. */
  void set_h(int h) {r.h = h;}
  void set(int x, int y, int w, int h);

  /** Cast rect to SDL_Rect. */
  operator SDL_Rect() { return r; }
  /** Cast rect to a SDL_Rect* */
  operator SDL_Rect*() { return &r; }
  /** Cast rect to a point. */
  operator point() { return point(r.x, r.y); }


  rect &operator+=(point p);
  rect &operator-=(point p);
  rect operator+(point p);
  rect operator-(point p);
  
protected:
  SDL_Rect r;
};



#endif
