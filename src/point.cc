#include "point.h"

/** Default constructor. */
point::point() {
  x=y=0;
}

/** Create a point.
 * @param x x-coord.
 * @param y y-coord.
 */
point::point(int x, int y) {
  this->x = x;
  this->y = y;
}

/** Copy constructor. */
point::point(const point& p) {
  x = p.x;
  y = p.y;
}


/* Get distance from origo. */
float point::distance() {
  return sqrt(float(x*x + y*y));
}


/** Get distance between two points. 
 * @param p the other point... */
float point::distance(point &p) {
  int x = this->x - p.x;
  int y = this->y - p.y;
  return sqrt(float(x*x + y*y));
}


/** Addition of two points. */
point operator+(point& p1, point& p2) { 
  return point(p1.x+p2.x, p1.y+p2.y); 
}


/** Subtraction of two points. */
point operator-(point& p1, point& p2) { 
  return point(p1.x-p2.x, p1.y-p2.y); 
}


/** Multiplication of a point and a scalar. */
point operator*(point& p, int scalar) { 
  return point(p.x*scalar, p.y*scalar); 
}


/** Division of a point and a scalar. */
point operator/(point& p, int scalar) { 
  return point(p.x/scalar, p.y/scalar);
}
