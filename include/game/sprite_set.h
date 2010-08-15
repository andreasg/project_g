
#ifndef PG_GAME_SPRITE_SET_H
#define PG_GAME_SPRITE_SET_H

#include <vector>
#include <list>
#include "sprite.h"
#include "sprite_manager.h"

class sprite;

typedef std::list<sprite*> sprite_list;
typedef std::list<sprite*>::iterator sprite_list_iter;


/** Containment class for sprites. */
class sprite_set {
public:
  sprite_set();
  virtual ~sprite_set();

  sprite *add_sprite(sprite *s);
  void remove_sprite(sprite *s);

  void update();
  void draw(canvas *c);

  int size();
  
  sprite_list *get_sprites() {return &sprites;}

private:
  sprite_list sprites;
};

typedef std::vector<sprite_set*> sprite_set_vector;
typedef std::vector<sprite_set*>::iterator sprite_set_vector_iter;


typedef sprite_set_vector layer_set;
typedef sprite_set_vector_iter layer_set_iter;

#endif
