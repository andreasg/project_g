
#include "main_canvas.h"

/** Default constructor.
 * This will create a screen.
 * @param w width of the display area
 * @param h height of the display area
 * @param bpp the pixel-depth for the display.
 * @param flags sdl flags for the surface. */
main_canvas::main_canvas(int w, int h, int bpp, int flags) : canvas(SDL_SetVideoMode(w, h, bpp, flags)) {
}

/** Default destructor. */
main_canvas::~main_canvas() {}
