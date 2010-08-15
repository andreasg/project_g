
#include "game/animation.h"

/** Part of the picture that will be drawn. */
color animation::clip_color = color(0,0,255);

/** The coord of the offset-point. */
color animation::offset_color = color(0,255,0);


/** Default constructor. */
animation::animation() {
  current_frame = 0;
  playing = false;
}


/** Default destructor. */
animation::~animation() {
}


/** Load the frames for an animation. 
 * A frame-file is a bitmap with several frames within it, on a single row.  
 * each frame have a horizontal and a vertical row that contains information
 * about the frame.
 * @param filename file with the frames.
 * @param frame_w width of the frame.
 * @param frame_h height of the frame.
 * @return pointer to a new animation object. */
animation* animation::open_animation(std::string filename, int frame_w, int frame_h) {
 
  /* load image */
  canvas *image = canvas::load_bmp_compatible(filename);
  if (image == NULL) {
    fprintf(stderr, "animation::open_animation(): failed to open animation file.");
    exit(1);
  }
  canvas *c = NULL;
  animation *anim = new animation();

  rect dest_rect(0,0, frame_w, frame_h);
  rect frame_clip_rect(1,1, frame_w-1, frame_h-1);

  for (rect src_rect(0,0,frame_w, frame_h); src_rect.get_x() < image->get_w(); src_rect+=point(frame_w, 0)) {
    /* copy out the frame*/
    c = canvas::create_rgb_compatible(SDL_ANYFORMAT, frame_w, frame_h);
    c->blit(dest_rect, *image, src_rect);

    /* check the frame data and create anchorpoint and clip_rect. */
    rect clip_rect(0,0,0,0);
    point offset(0,0);
    bool clip_started = false;

    /* scan the horizontal frame */
    c->lock();
    c->set_color_key(c->get_pixel(0,0));
    for (int x=0,y=0; x<frame_w; x++) {
      color col = c->get_pixel(x,y);
      if (col == animation::clip_color) {
        if (!clip_started) {
          clip_rect.set_x(x);
          clip_started=true;
        } else {
          clip_rect.set_w(x - clip_rect.get_x());
        }
      } else if (col == animation::offset_color) {
        offset.set_x(x);
      }
    }

    /* scan the vertical frame */
    clip_started = false;
    for (int x=0,y=0; y<frame_h; y++) {
      color col = c->get_pixel(x,y);
      if (col == animation::clip_color) {
        if (!clip_started) {
          clip_rect.set_y(y);
          clip_started=true;
        } else {
          clip_rect.set_h(y - clip_rect.get_y());
        }
      } else if (col == animation::offset_color) {
        offset.set_y(y);
      }
    }
    c->unlock();

    /* put it into a picture and add to set. */
    anim->add_picture(new picture(c, clip_rect, offset));
  }

  /* clean up. */
  delete image;

  return anim;
}


/** True if animation is playing. */
bool animation::is_playing() {
  return playing;
}


/** Play the animation. */
void animation::play() {
  playing = true;
}


/** Pause the animation. */
void animation::pause() {
  playing = false;
}


/** Pause and reset the animation. */
void animation::stop() {
  playing = false;
  current_frame = 0;
}


/** Flick the frames. */
void animation::flick() {
  if (current_frame++ >= size()-1)
    current_frame=0;
}


/** Flick the selected frame.\ Returning the next frame to be flicked. */
int animation::flick(int current_frame) {
  if (current_frame++ >= size()-1) 
    current_frame=0;
  return current_frame;
}


/** Draw the current frame. 
 * @param dest destination canvas.
 * @param pos where to place the frame. */
void animation::render(canvas *dest, point pos) {
  get_picture(current_frame)->place(dest, pos);
}
