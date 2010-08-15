#ifndef PG_GAME_ANIMATION_H
#define PG_GAME_ANIMATION_H

#include <string>
#include <vector>


#include "../color.h"
#include "../canvas.h"
#include "../picture_set.h"


/** Animation.
 * Provides control and containment for an animation. */
class animation : public picture_set {
public:
  animation();
  virtual ~animation();

  static animation* open_animation(std::string filename, int frame_w, int frame_h);

  bool is_playing();

  void play();
  void pause();
  void stop();

  void flick();
  int flick(int current_frame);

  void render(canvas *dest, point pos);

  static color clip_color;
  static color offset_color;

private:
  bool playing;
  int current_frame;
};


#endif
