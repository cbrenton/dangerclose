#ifndef _WAVY_H
#define _WAVY_H

#include <math.h>
#include "geom/geometry.h"

class Wavy : public Geometry
{
   public:
      Wavy(glm::vec3 _normal, float _offset);
      ~Wavy() {};
      float dist(glm::vec3 *pt, glm::vec3 *dir = NULL);
      void debug();
   private:
      glm::vec3 normal;
      float offset;
};

#endif
