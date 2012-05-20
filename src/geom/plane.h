#ifndef _PLANE_H
#define _PLANE_H

#include "geom/geometry.h"
#include "light.h"

class Plane : public Geometry
{
   public:
      Plane(glm::vec3 _normal, float _offset);
      ~Plane() {};
      float dist(glm::vec3 *pt, glm::vec3 *dir = NULL);
      void debug();
   private:
      glm::vec3 normal;
      float offset;
};

#endif
