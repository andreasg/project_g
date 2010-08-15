#include "picture_set.h"


/** Default constructor.\ Create an empty set. */
picture_set::picture_set() {}


/** Default destructor. */
picture_set::~picture_set() {
  if (!pics.empty()) {
    for(picture_vector_iter it=pics.begin(); it!=pics.end(); it++) {
      delete (*it);
    }
  }
}


/** Add a picture to the set.
 * @param p pointer to a picture to add. */
void picture_set::add_picture(picture *p) {
  if (p) pics.push_back(p);
}


/** Check if picture is in set.
 * @param p pointer to the picture. 
 * @return true if found, else false. */
bool picture_set::has_picture(picture *p) {
  return (find_picture(p) != -1);
}


/** Find the index of a picture in the set.
 * @param p the picture. 
 * @return the index of the picture, -1 if not found. */
int picture_set::find_picture(picture *p) {
  int i=0;
  for(picture_vector_iter it=pics.begin(); it!=pics.end(); it++, i++) {
    if ((*it) == p) return i;
  }
  return -1;
}


/** Remove a picture from the set. */
void picture_set::remove_picture(picture *p) {
  pics.erase(pics.begin() + find_picture(p));
}


/** Get a pointer to a picture in the set.
 * @param index what picture to get.
 * @return pointer to the picture, NULL if not found. */
picture *picture_set::get_picture(int index) {
  if (0 <= index && index < (signed int)pics.size())
    return pics[index];
  else
    return NULL;
}

/** How many pictures there are in the set. */
int picture_set::size() {
  return pics.size();
}
