#ifndef PG_TIMER_H
#define PG_TIMER_H

#include <string>
#include <iostream>

#include <SDL.h>
#include "message_handler.h"

/** Abstracts timers in SDL. */
class timer : public message_handler {
public:
  timer() : message_handler(NULL)  {}
  virtual ~timer() {}

  /** Get the interval of the timer-pulse. */
  int get_interval() { return (int)interval; }

  /** Set the interval of the timer-pulse. */
  void set_interval(int inter) { interval = (Uint32)inter; }

  /** Get the id of the timer. */
  SDL_TimerID get_timer_id() {return id;}

  /** Start the timer. */
  void start() { id = SDL_AddTimer(interval, timer_proc, this); }

  /** Stop the timer. */
  void stop() { SDL_RemoveTimer(id); id=0;}

  /** Called when the timer pulses. */
  virtual void on_timer();

private:
  SDL_TimerID id;
  Uint32 interval;

  /** Allows us to abstract many different timers. Simply calls the 
   * on_timer() in each class. It is called by SDL.
   * @see on_timer() */
  static Uint32 timer_proc(Uint32 interval, void *param);
};


#endif
