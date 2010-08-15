#ifndef PG_APPLICATION_H
#define PG_APPLICATION_H

#include <cstdio>
#include <SDL.h>

#include "message_handler.h"


/**
 * Abstraction of an application.
 *
 * A singleton  that provides a simple main loop for 
 * a SDL application.
 */
class application : public message_handler {
public:

  /** Default constructor. */
  application();

  /** Default destructor. */
  virtual ~application();

  /** Called by on_exec(), before the main-loop is started.
   * @see on_exec()
   * @return true if success, else false.
   */
  virtual bool on_init(int argc, char **argv);

  /** When an event occurs within the main loop, on_event() is called. */
  virtual void on_event(SDL_Event *e);

  /** When nothing is to do. */
  virtual void on_idle();

  /** Called before quitting the application. */
  virtual void on_exit();

  /** The main-loop.
   * @param argc length of argv
   * @param argv the command-line arguments passed to the application.
   * @return the exit-code for the application.
   */
  static int exec(int argc, char **argv);

  /** get a pointer to the application. 
   * @return pointer to the application. 
   */
  static application *get_application() {return app;}

  /** When we get a message - this parses it.
   * @return true if we handeled the message, else false.
   */
  virtual bool on_message(msgid msg, void *param1, void *param2, void *param3, void *param4);

  /** Static message that we can send to an application to quit it. */
  static msgid msgid_exit_application;

  /** Indicates if the application's main-loop are running. */
  static bool running;

protected:
  unsigned int window_width;
  unsigned int window_height;

private:
  static application *app;
  static void set_application(application *a);
};



#endif
