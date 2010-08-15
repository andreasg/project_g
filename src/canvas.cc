#include "canvas.h"


/** Default constructor.
 * @param s Surface to work with. */
canvas::canvas(SDL_Surface *s) {
  surface = s;
}


/** Defualt destructor. */
canvas::~canvas() {
  if (surface) {
    SDL_FreeSurface(surface);
  }
}


/** Get the surface.
 * @return pointer to the surface. */
SDL_Surface *canvas::get_surface() {
  return surface;
}


/** Lock the surface for per-pixel operations.
 * @note This must be done before get_pixel and set_pixel are used. */
void canvas::lock() {
  SDL_LockSurface(surface);
}


/** Unlock the surface.
 * @see lock() 
 * @note Should be called after get-/set-pixel are used. */
void canvas::unlock() {
   SDL_UnlockSurface(surface);
}


/** Get the color of a pixel.\ The canvas must be locked for this to work.
 * @see lock()
 * @note Must call lock() before use.
 * @param x x-coordinate for the pixel.
 * @param y y-coordinate for the pixel.
 * @return color of the pixel.*/
color canvas::get_pixel(int x, int y) {
  Uint8 r,g,b;
  Uint32 *pixel = (Uint32*)surface->pixels;

  pixel += y*(surface->pitch/4);
  pixel += x;

  SDL_GetRGB(*pixel, surface->format, &r, &g, &b);
  color c(r,g,b);
  return c;
}


/** Set the color of a pixel.\ The canvas must be locked for this to work.
 * @see lock()
 * @note Must call lock() before use.
 * @param x x-coordinate for the pixel.
 * @param y y-coordinate for the pixel.
 * @param c new color for the pixel. */
void canvas::set_pixel(int x, int y, color &c) {
  Uint32 *pixel = (Uint32*)surface->pixels;
  pixel += y*(surface->pitch/4);
  pixel += x;
  (*pixel) = c.map(surface->format);
}


/** Get the width of the canvas. 
 * @return the width of the canvas. */
int canvas::get_w() {
  return surface->w;
}


/** Get the height of the canvas. 
 * @return the height of the canvas. */
int canvas::get_h() {
  return surface->h;
}


/** Add a rect for a part of the canvas that needs
 * to be updated.
 * @param r the rectangle to be updated. */
void canvas::add_update_rect(rect r) {
  update_rects.push_back(r);
}


/** Clear all update-rects. */
void canvas::clear_update_rects() {
  update_rects.clear();
}


/** Update the parts specified by all the 
 * update-rectangles.\ This will clear the update-rects. */
void canvas::update_rectangles() {
  for(rect_list_iter it=update_rects.begin(); it!=update_rects.end(); it++) {
    SDL_UpdateRect(surface, (*it)->x, (*it)->y, (*it)->w, (*it)->h);
  }
  clear_update_rects();
}


/** Update the whole canvas. */
void canvas::flip(){
  if (surface != NULL) SDL_Flip(surface);
}


/** Set the color for transparancy.
 * @param c The transparent color.
 * @return true if success else false. */
bool canvas::set_color_key(color c) {
  if (SDL_SetColorKey(surface, SDL_SRCCOLORKEY, c.map(surface->format)) == 0) return true;
  return false;
}

/** Reset the color-key. */
void canvas::clear_color_key() {
  SDL_SetColorKey(surface, 0, 0);
}


/** Set the clipping rect for the canvas.\ This 
 * will determine what parts of the canvas that are blitted.
 * @param r the new clip-rect. */
void canvas::set_clip_rect(rect *r) {
  SDL_SetClipRect(surface, *r);
}


/** Get the clip-rect.
 * @return the clip-rect. */
rect canvas::get_clip_rect() {
  rect r;
  SDL_GetClipRect(surface, r);
  return r;
}


/** Fill the entire rectangle with a color.
 * @param r the rectangle to fill.
 * @param c the color to fill with. */
bool canvas::fill_rect(rect &r, color &c) {
  if (SDL_FillRect(surface, r, c.map(surface->format)) == 0) return true;
  return false;
}


/** Clear the entire surface to a solid color.
 * @param c the color to use. */
bool canvas::clear(color &c) {
  if (SDL_FillRect(surface, NULL, c.map(surface->format)) == 0) return true;
  else return false;
}


/** Blit a canvas onto this.
 * @param dest_rect a rectangle specifying the destination on this canvas.
 * @param src the canvas to blit onto this.
 * @param src_rect the parts of src to blit.
 * @return true if success else false */
bool canvas::blit(rect &dest_rect, canvas &src, rect &src_rect) {
  if (SDL_BlitSurface(src, src_rect, surface, dest_rect) == 0) {
    add_update_rect(dest_rect);
    return true;
  }
  return false;
}


/** Create a canvas with a surface assocciated with it.
 * @param flags 
 *          - available flags
 *           - SDL_HWSURFACE
 *           - SDL_SWSURFACE
 *           - SDL_ANYFORMAT
 *           - SDL_HWPALETTE
 *           - SDL_DOUBLEBUF
 *           - SDL_FULLSCREEN
 *           - SDL_OPENGL
 *           - SDL_OPENGLBLIT
 *           - SDL_RESIZABLE
 *           - SDL_HWACCEL
 *           - SDL_SRCCOLORKEY
 *           - SDL_RLEACCEL
 *           - SDL_SRCALPHA
 *           - SDL_PREALLOC
 * @param w width of the surface.
 * @param h height of the surface.
 * @param depth how many bits for colors.
 * @return pointer to a new canvas. */
canvas *canvas::create_rgb(Uint32 flags, int w, int h, int depth,
                           Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask) {
  SDL_Surface *s = SDL_CreateRGBSurface(flags, w, h, depth, rmask, gmask, bmask, amask);
  if (s) return new canvas(s);
  else return NULL;
}


/** Create a canvas with a surface, compatible with the display-surface.
 * @param flags @see create_rgb_surface()
 * @param w width of surface.
 * @param h height of surface.
 * @param depth how many bits for colors.
 * @return pointer to a new canvas. */
canvas *canvas::create_rgb_compatible(Uint32 flags, int w, int h) {
  SDL_Surface *s = SDL_DisplayFormat(SDL_CreateRGBSurface(flags, w, h, 0,0,0,0,0));
  if (s) return new canvas(s);
  else return NULL;
}


/** Load a bitmap.
 * @param filename filename of the bitmap.
 * @return pointer to a new canvas with the bitmap within it. */
canvas *canvas::load_bmp(std::string filename) {
  //  SDL_Surface *bmp = SDL_LoadBMP(filename.c_str());
  SDL_Surface *bmp = IMG_Load(filename.c_str());
  if (bmp) return new canvas(bmp);
  else return NULL;
}                                


/** Load a bitmap.
 * @param filename filename of the bitmap.
 * @return pointer to a new canvas  compatible with the display-surface.
 */
canvas *canvas::load_bmp_compatible(std::string filename) {
  canvas *c = canvas::load_bmp(filename);
  if (c) {
    SDL_DisplayFormat(c->get_surface());
    return c;
  }
  return NULL;
}


  
