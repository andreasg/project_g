#ifndef PG_CANVAS_H
#define PG_CANVAS_H

#include "message_handler.h"
#include "color.h"
#include "rect.h"

#include <cstdlib>
#include <string>
#include <list>

#include <SDL_image.h>


/** List of rectangles. */
typedef std::list<SDL_Rect*> rect_list;

/** Iterator for a list of rectangles. */
typedef std::list<SDL_Rect*>::iterator rect_list_iter;


/** Provides an abstraction around an SDL_Surface. */
class canvas {
public:
  canvas(SDL_Surface *s=NULL);
  virtual ~canvas();

  SDL_Surface *get_surface();

  void lock();
  void unlock();

  color get_pixel(int x, int y);
  void set_pixel(int x, int y, color &c);

  int get_w();
  int get_h();

  void add_update_rect(rect r);
  void clear_update_rects();
  void update_rectangles();
  void flip();

  bool set_color_key(color c);
  void clear_color_key();

  void set_clip_rect(rect *r);
  rect get_clip_rect();

  bool fill_rect(rect &r, color &c);
  bool clear(color &c);
  bool blit(rect &dest_rect, canvas &src, rect &src_rect);

  static canvas *create_rgb(Uint32 flags, int w, int h, int depth, 
                            Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask);
  static canvas *create_rgb_compatible(Uint32 flags, int w, int h);
  static canvas *load_bmp(std::string filename);
  static canvas *load_bmp_compatible(std::string filename);

  /** Cast canvas to SDL_Surface*.*/
  operator SDL_Surface*() {return surface;}
  
  /** Cast canvas to SDL_Surface. */
  operator SDL_Surface() {return (*surface);}

private:
  SDL_Surface *surface;
  rect_list update_rects;
};


#endif
