#ifndef PG_PICTURE_SET_H
#define PG_PICTURE_SET_H

#include "picture.h"

#include <vector>

/** A vector of pictures. */
typedef std::vector<picture*> picture_vector;

/** Iterator for a vector of pictures. */
typedef std::vector<picture*>::iterator picture_vector_iter;


/** Container-class for pictures. */
class picture_set {

public:
  picture_set();
  virtual ~picture_set();

  void add_picture(picture *p);
  bool has_picture(picture *p);
  int find_picture(picture *p);
  void remove_picture(picture *p);
  picture *get_picture(int index);
  
  int size();

protected:
  /** Vector of pictures. */
  picture_vector pics;
};

#endif
