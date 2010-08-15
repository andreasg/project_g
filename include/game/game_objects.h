
#ifndef PG_GAME_GAME_OBJECTS_H
#define PG_GAME_GAME_OBJECTS_H

#include "canvas.h"

/**
 * State class. Use to manage objects states.
 */
class state {
public:
  state() : n_states(0), state_id(0) {}
  virtual ~state() {}

  int get_state();
  void next_state();
  void set_state(int state_id);

private:
  /** How many states. */
  int n_states;

  /** Current state. */
  int state_id;
};


/**
 * The most basic primitive for a game. */
class game_object {
public:
  game_object() {}
  virtual ~game_object() {}
};


/** Baseclass for any object that are to be rendered. */
class renderable : game_object {
public:
  renderable() {}
  virtual ~renderable() {}

  bool render(canvas* dest);
};


/** Baseclass for any object that do not wish to be rendered. */
class non_renderable : game_object {
public:
  non_renderable() {}
  virtual ~non_renderable() {}
};


#endif
