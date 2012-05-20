#ifndef _SPHERE_H
#define _SPHERE_H

#include "geom/geometry.h"

class Sphere : public Geometry
{
   public:
      Sphere();
      Sphere(float _rad);
      ~Sphere() {};
      float dist(glm::vec3 *pt);
      glm::vec3 getNormal(glm::vec3 *pt);
      //glm::vec3 cdNormal(glm::vec3 *pt);
      void debug();
   private:
      float rad;
};

#endif
