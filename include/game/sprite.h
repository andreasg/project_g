
#ifndef PG_GAME_SPRITE_H
#define PG_GAME_SPRITE_H

#include "../point.h"
#include "../rect.h"
#include "../vector.h"
#include "../canvas.h"
#include "animation.h"

#include "game/sprite_manager.h"

typedef std::vector<animation*> animation_vector;

/** Baseclass for sprites. 
 * Outlines some simple functionallity for sprites.
 * - Movement
 * - Collisions
 * - Blitting
 * - Animating */
class sprite {
public:
  sprite(int id=0);
  virtual ~sprite();

  int get_id();
  void set_id(int id);

  int add_animation(animation *anim);
  void select_animation(int index);

  animation *get_current_animation();

  virtual void update();

  void draw(canvas *dest);

  void set_colliding(bool b);
  bool is_colliding();

  void set_collision_rect(rect r);
  rect get_collision_rect();

  void set_position(point pos);
  point get_position();

  void set_movement(point v, float speed);

  void set_movement_vector(point v);
  point get_movement_vector();

  float get_speed();
  void set_speed(float speed);
  
protected:
  /** The sprites position. */
  vector position;

  /** Movement vector */
  vector movement_vector;

  /** The speed of the sprite. */
  float speed;

private:
  /** Vector of animations (jump, run, walk etc.) */
  animation_vector animations;

  /** Current playing animation. */
  animation *current_animation;

  /** Determine if this is a collision object or not. */
  bool colliding;

  /** The collisions rect. */
  rect collision_rect;

  /** Id of the sprite. */
  int id;
};

#endif
