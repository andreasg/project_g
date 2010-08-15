
#ifndef PG_GAME_SPRITE_MANAGER_H
#define PG_GAME_SPRITE_MANAGER_H


#include <map>
#include <list>

#include "game/sprite.h"
#include "game/sprite_set.h"

#include <iostream>

class sprite;
class sprite_set;

/** Manages sprites and their associations to sprite_set's. */
namespace sprite_manager {
  void associate(sprite *s, sprite_set *set);
  void remove_association(sprite *s, sprite_set *set);
  void delete_sprite(sprite *s);
  int size();

  extern std::map<sprite*, std::list<sprite_set*> > sprite_map;
} 

#endif
