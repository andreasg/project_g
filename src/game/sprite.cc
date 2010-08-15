#include "game/sprite.h"


/** Create a sprite.
 * @param id the id of the sprite. */
sprite::sprite(int id) {
  this->id = id;
  current_animation = NULL;
  speed = 0.0f;
  colliding = false;
}


/** Default destructor. 
 * Will free all animations in the sprite from memory. */
sprite::~sprite() {
  sprite_manager::delete_sprite(this);
  if (animations.empty() == true) {
    for(animation_vector::iterator it=animations.begin(); it!=animations.end(); it++) {
      delete (*it);
    }
  }
}


/** Get the id of the sprite. */
int sprite::get_id() {
  return id;
}


/** Set the id of the sprite. */
void sprite::set_id(int id) {
  this->id = id;
}


/** Adds an animation to the animation-list.
 * @note You have to keep track of the index
 *       your self. */
int sprite::add_animation(animation *anim) {
  animations.push_back(anim);
  return animations.size()-1;
}


/** Select what animation to play. */
void sprite::select_animation(int index) {
  if ((unsigned)index >= animations.size()) {
    return;
  }
  
  if (current_animation)
    current_animation->stop();

  current_animation = animations[index];
}


/** Get a pointer to the current animation. */
animation *sprite::get_current_animation() {
  return current_animation;
}


/** Update the sprite.
 * This is called to update the sprite and should 
 * perform whateven is to happen to the sprite, 
 * movement, collision etc. */
void sprite::update() {
}


/** Draw the sprite. */
void sprite::draw(canvas *dest) {
  if (current_animation) {
    current_animation->render(dest, position);
  }
}


/** Set the colliding status of the sprite, 
 * if false - sprite cannot colide with any other sprites. 
 * @param b true for collide, else false. */
void sprite::set_colliding(bool b) {
  colliding  = b;
}


/** Get the colliding status of the sprite. */
bool sprite::is_colliding() {
  return colliding;
}


/** Set the collision rectangle.
 * A collision-rect is what is used when 
 * collision detection is done on the sprite.
 * 
 * The x and y coords are relative to the 
 * sprites position.
 * @param r the collision rect. */
void sprite::set_collision_rect(rect r) {
  collision_rect = r;
}


/** Get the collision rectangle.
 * @see set_collision_rect . */
rect sprite::get_collision_rect() {
  return collision_rect;
}


/** Set the position of the sprite.
 * @param pos the new position. */
void sprite::set_position(point pos) {
  position = pos;
}


/** Get the sprites current position. */
point sprite::get_position() {
  return position;
}


/** Change the vector and speed of the sprite. */
void sprite::set_movement(point v, float speed) {
  movement_vector = v;
  set_speed(speed);
}


/** Set the movement-vector.
 * This will set the new vector - normalize it, and
 * then multply it with the sprites current speed. If you
 * wish to change both vector and speed, use set_movement().
 * @see set_movement() */
void sprite::set_movement_vector(point v) {
  movement_vector = v;
  movement_vector.normalize();
  movement_vector *= speed;
}


/** Get the speed of the sprite. */
float sprite::get_speed() {
  return speed;
}


/** Set the speed of the sprite. */
void sprite::set_speed(float speed) {
  this->speed = speed;
  movement_vector.normalize();
  movement_vector *= speed;
}
