
#ifndef PG_VECTOR_H
#define PG_VECTOR_H

#include <cmath>

#include "point.h"


/** A vector is a point in space.\ It can be seen as a
 * precision version of point (using float's instead of int's).
 * @see point */
class vector {
public:
  vector();
  vector(float x, float y);
  vector(vector &v);
  vector(point &p);
  virtual ~vector();

  void set_x(float x);
  void set_y(float y);
  float get_x();
  float get_y();

  float length();
  
  void normalize();

  operator point();

  vector operator*(float scalar);
  vector operator/(float scalar);
  vector& operator+=(vector &v);
  vector& operator-=(vector &v);
  vector& operator*=(float scalar);
  vector& operator/=(float scalar);

private:
  float x, y;
};


#endif
