#ifndef PG_EVENTHANDLER_H
#define PG_EVENTHANDLER_H


#include "application.h"
#include "ui/control.h"


/** Abstraction of a SDL event handler. */
class event_handler : public application {
public:

  /** Default constructor. */
  event_handler() {};

  /** Default destructor. */
  virtual ~event_handler() {};

  /** Parse the event and dispatch to correct sub-funcion.
   * @param e event to parse. 
   */
  virtual void on_event(SDL_Event *e);

  /** Filter events, override this to control exactly
   * what events to act on, and filter out the rest.
   * @param e event to parse.
   * @return true if event was filtered, else false.
   */
  virtual bool filter_event(SDL_Event *e);

  /** Called when application gains keyboard focus. */
  virtual void on_input_focus(){}

  /** Called when application looses keyboard focus. */
  virtual void on_input_blur(){}

  /** Called when window gains mouse focus. */
  virtual void on_mouse_focus(){}

  /** When window looses mouse focus. */
  virtual void on_mouse_blur(){}

  /** Called when the window is minimized. */
  virtual void on_minimize(){}

  /** Called when the window is restored after beeing minimized  */
  virtual void on_restore(){}

  /** Called when a key is pressed.
   * @param k key that was pressed.
   * @param m modifier-keys that was pressed.
   * @param unicode used by sdl.
   */
  virtual void on_key_down(SDLKey k, SDLMod m, Uint16 unicode){}

  /** Called when a key is released.
   * @param k key that was released.
   * @param m modifier-keys that was released.
   * @param unicode used by sdl.
   */
  virtual void on_key_up(SDLKey k, SDLMod m, Uint16 unicode){}

  /** Called when the mouse is moved.
   * @param x x-coordinate of the pointer.
   * @param y y-coordinate of the pointer.
   * @param relx relative x-motion.
   * @param rely relative y-motion.
   * @param left true if left mousebutton is pressed.
   * @param right true if left mousebutton is pressed.
   * @param middle true if left mousebutton is pressed.
   */
  virtual void on_mouse_move(int x, int y, int relx, int rely,
                             bool left, bool right, bool middle) {}

  /** Called on left mousebutton down.
   * @param x x-coordinate of the pointer.
   * @param y y-coordinate of the pointer.
   */
  virtual void on_lbutton_down(int x, int y){}

  /** Called on left mousebutton up.
   * @param x x-coordinate of the pointer.
   * @param y y-coordinate of the pointer.
   */
  virtual void on_lbutton_up(int x, int y){}

  /** Called on right mousebutton down.
   * @param x x-coordinate of the pointer.
   * @param y y-coordinate of the pointer.
   */
  virtual void on_rbutton_down(int x, int y){} 

  /** Called on right mousebutton up.
   * @param x x-coordinate of the pointer.
   * @param y y-coordinate of the pointer.
   */
  virtual void on_rbutton_up(int x, int y) {}

  /** Called on middle mousebutton down.
   * @param x x-coordinate of the pointer.
   * @param y y-coordinate of the pointer.
   */
  virtual void on_mbutton_down(int x, int y) {}

  /** Called on middle mousebutton up.
   * @param x x-coordinate of the pointer.
   * @param y y-coordinate of the pointer.
   */
  virtual void on_mbutton_up(int x, int y) {}

  
  /** Called when the window is resized.
   * @param w new width of the window.
   * @param h new height of the window.
   */
  virtual void on_resize(int w, int h) {}

  virtual void on_expose() {}

  virtual void on_user(int type, int code, void *data1, void *data2) {}
};

#endif
