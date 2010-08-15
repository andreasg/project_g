
#include "color.h"


/** Create a color with custom itensity.
 * @param r Red intensity.
 * @param g Green intensity.
 * @param b Blue intensity. */
color::color(Uint8 r, Uint8 g, Uint8 b) {
  col.r = r;
  col.g = g;
  col.b = b;
}


/** Copy constructor. */
color::color(const color &c) {
  col.r = c.col.r;
  col.g = c.col.g;
  col.b = c.col.b;
}


/** Set the red intensity. */
void color::set_r(Uint8 r) {
  col.r = r;
}

/** Set the blue intensity. */
void color::set_g(Uint8 g) {
  col.g = g;
}

/** Set the blue intensity. */
void color::set_b(Uint8 b) {
  col.b = b;
}


/** Get the red intensity. */
Uint8 color::get_r() {
  return col.r;
}


/** Get the green intensity. */
Uint8 color::get_g() {
  return col.g;
}


/** Get the blue intensity. */
Uint8 color::get_b() {
  return col.b;
}


/** Cast to SDL_Color. */
color::operator SDL_Color() {
  return col;
}


/** Cast to SDL_Color*. */
color::operator SDL_Color*() {
  return &col;
}


/** Compare two colors. */
bool color::operator==(color &c) {
  return (col.r == c.col.r &&
          col.g == c.col.g &&
          col.b == c.col.b);
}


/** Compare two colors. */
bool color::operator!=(color &c) {
  return !((*this)==c);
}


/** Change the intensity of the color. */
color &color::operator+=(int i) {
  set_r(col.r+i);
  set_g(col.g+i);
  set_b(col.b+i);
  return *this;
}


/** Change the intensity of the color. */
color &color::operator-=(int i) {
  set_r(col.r-i);
  set_g(col.g-i);
  set_b(col.b-i);
  return *this;
}


/** Default color. */
color color::red(Uint8 intensity) {
  color c(intensity, 0, 0);
  return c;
}


/** Default color. */
color color::green(Uint8 intensity) {
  color c(0, intensity, 0);
  return c;
}


/** Default color. */
color color::blue(Uint8 intensity) {
  color c(0, 0, intensity);
  return c;
}
