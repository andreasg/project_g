
#include "game/sprite_manager.h"

namespace sprite_manager {


  /** Associates a sprite with sprite_set's. */
  std::map<sprite*, std::list<sprite_set*> > sprite_map;


  /** Associate a sprite_set to a sprite. */
  void associate(sprite *s, sprite_set *set) {
    sprite_map[s].push_front(set);
  }


  /** De-associate a sprite_set from a sprite. */
  void remove_association(sprite *s, sprite_set *set) {
    if (sprite_map.find(s) != sprite_map.end())
      sprite_map[s].remove(set);
  }


  /** Delete entry from the sprite_manager, 
   * removing the sprite from all associated sprite_set's. */
  void delete_sprite(sprite *s) {
    std::map<sprite*, std::list<sprite_set*> >::iterator pos;
    if ((pos=sprite_map.find(s)) != sprite_map.end()) {
      // remove the sprite from all the set's it's within.
      if (!sprite_map[s].empty()) {
        std::list<sprite_set*>::iterator it;
        for (it=sprite_map[s].begin(); it!=sprite_map[s].end(); it++) {
          remove_association(s, *it);
        }
        // clear out the set's (may be covered below by the erase() call).
        sprite_map[s].clear();
      }

      // remove the sprite from our manager.
      //sprite_map.erase(pos);
    }
  }


  /** Get the number of sprites currently associated with a set. */
  int size() {
    return sprite_map.size();
  }
}
