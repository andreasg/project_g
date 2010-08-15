
#include "vector.h"


/** Default constructor. */
vector::vector() {
  x = 0.0f;
  y = 0.0f;
}


/** Create a vector from coords.
 * @param x x-coord.
 * @param y y-coord. */
vector::vector(float x, float y) {
  this->x = x;
  this->y = y;
}


/** Copy constructor. */
vector::vector(vector &v) {
  x = v.x;
  y = v.y;
}


/** Create a vector from a point. */
vector::vector(point &p) {
  x = static_cast<float>(p.get_x());
  y = static_cast<float>(p.get_y());
}


/** Default destructor. */
vector:: ~vector() {
}


/** Set the x-coord for the vector. */
void vector::set_x(float x) {
  this->x = x;
}


/** Set the y-coord for the vector. */
void vector::set_y(float y) {
  this->y = y;
}


/** Get the x-coord for the vector. */
float vector::get_x() {
  return x;
}


/** Get the y-coord for the vector. */
float vector::get_y() {
  return y;
}


/** Get the vector's length. */
float vector::length() {
  return sqrt(x*x + y*y);
}


/** Normalize the vector (set it's length to 1). */
void vector::normalize() {
  float len = length();
  x /= len;
  y /= len;
}


/** Cast the vector to a position. */
vector::operator point() {
  return point(static_cast<int>(x), static_cast<int>(y));
}


/** Create a vector with different length. */
vector vector::operator*(float scalar) {
  vector v(x*scalar, y*scalar);
  return v;
}


/** Create a vector with different length. */
vector vector::operator/(float scalar) {
  vector v(x/scalar, y/scalar);
  return v;
}


/** Change the position of the sprite. */
vector& vector::operator+=(vector &v) {
  x += v.x;
  y += v.y;
  return *this;
}


/** Change the position of the sprite. */
vector& vector::operator-=(vector &v) {
  x -= v.x;
  y -= v.y;
  return *this;
}


/** Modify the length of the vector. */
vector& vector::operator*=(float scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}


/** Modify the length of the vector. */
vector& vector::operator/=(float scalar) {
  x /= scalar;
  y /= scalar;
  return *this;
}
