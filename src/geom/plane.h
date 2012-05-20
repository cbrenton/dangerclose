#ifndef _PLANE_H
#define _PLANE_H

#include "geom/geometry.h"

class Plane : public Geometry
{
   public:
      Plane();
      Plane(glm::vec4 _coefficients);
      ~Plane() {};
      float dist(glm::vec3 *pt);
      glm::vec3 getNormal(glm::vec3 *pt);
      void debug();
   private:
      glm::vec4 coefficients;
};

#endif