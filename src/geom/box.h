#ifndef _BOX_H
#define _BOX_H

#include "geom/geometry.h"

class Box : public Geometry
{
   public:
      Box();
      Box(float _size);
      ~Box() {};
      float dist(glm::vec3 *pt, glm::vec3 *dir = NULL);
      void debug();
   private:
      float size;
};

#endif
