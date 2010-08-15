#include "game/sprite_set.h"


/** Default constructor. */
sprite_set::sprite_set() {
}


/** Default destructor.\ Will NOT free the sprites in set from memory. */
sprite_set::~sprite_set() {
}


/** Add a sprite to the set.
 * @return pointer to the added sprite. NULL if sprite already was in set. */
sprite *sprite_set::add_sprite(sprite *s) {
  for (sprite_list_iter it=sprites.begin(); it!=sprites.end(); it++) {
    if (s == (*it)) return NULL;
  }

  sprites.push_back(s);
  sprite_manager::associate(s, this);
  return s;
}


/** Remove a sprite from the set.\ The sprite_set will no longer take 
 * responsability to free the sprite from memory. */
void sprite_set::remove_sprite(sprite *s) {
  for (sprite_list_iter it=sprites.begin(); it!=sprites.end(); it++) {
    if (s == (*it)) return;
  }

  sprites.remove(s);
  sprite_manager::remove_association(s, this);
}


/** Update the sprite set.
 * This will call the update() for all sprites in the set. */
void sprite_set::update() {
  sprite_list_iter it;
  for (it=sprites.begin(); it!=sprites.end(); it++) {
    (*it)->update();
  }
}

/** Draw all sprites in set onto a canvas. */
void sprite_set::draw(canvas *c) {
  if (c) {
    for (sprite_list_iter it = sprites.begin(); it!=sprites.end(); it++) {
      (*it)->draw(c);
    }
  }
}
    


/** Get how many sprites are in the set. */
int sprite_set::size() {
  return sprites.size();
}
