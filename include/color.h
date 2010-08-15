
#ifndef PG_COLOR_H
#define PG_COLOR_H

#include <SDL.h>

/** Abstraction of SDL_Color. */
class color {
public:
  color(Uint8 r=0, Uint8 g=0, Uint8 b=0);
  color(const color &c);

  virtual ~color() {}

  void set_r(Uint8 r);
  void set_g(Uint8 g);
  void set_b(Uint8 b);
  Uint8 get_r();
  Uint8 get_g();
  Uint8 get_b();

  operator SDL_Color();
  operator SDL_Color*();

  bool operator==(color &c);
  bool operator!=(color &c);
  color &operator+=(int i);
  color &operator-=(int i);

  /** Get the color packed into a single Uint32.
   * @param fmp The pixel-format of the canvas we will use the color on.
   * @return The color as an int. */
  Uint32 map(SDL_PixelFormat *fmt) {return SDL_MapRGB(fmt, col.r, col.g, col.b);}

  /** Red */
  static color red(Uint8 intensity=255);
  /** Green */
  static color green(Uint8 intensity=255);
  /** Blue */
  static color blue(Uint8 intensity=255);
private:
  SDL_Color col;
};

#endif 
