#ifndef _WAVY_H
#define _WAVY_H

#include <math.h>
#include "geom/geometry.h"

class Wavy : public Geometry
{
   public:
      Wavy();
      Wavy(glm::vec4 _coefficients);
      ~Wavy() {};
      float dist(glm::vec3 *pt);
      glm::vec3 getNormal(glm::vec3 *pt);
      void debug();
   private:
      glm::vec4 coefficients;
};

#endif
