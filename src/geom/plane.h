#ifndef _PLANE_H
#define _PLANE_H

#include "geom/geometry.h"

class Plane : public Geometry
{
   public:
      Plane();
      Plane(glm::vec3 _normal, float _offset);
      ~Plane() {};
      float dist(glm::vec3 *pt);
      void debug();
   private:
      glm::vec3 normal;
      float offset;
};

#endif
