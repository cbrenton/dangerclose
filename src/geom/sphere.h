#ifndef _SPHERE_H
#define _SPHERE_H

#include "geom/geometry.h"

class Sphere : public Geometry
{
   public:
      Sphere(float _rad);
      ~Sphere() {};
      float dist(glm::vec3 *pt, glm::vec3 *dir = NULL);
      void debug();
   private:
      float rad;
};

#endif
