#ifndef _SPHERE_H
#define _SPHERE_H

#include "geom/geometry.h"

#define lerp(t, a, b) ( a + t * (b - a) )

class Sphere : public Geometry
{
   public:
      Sphere(float _rad);
      ~Sphere() {};
      float dist(glm::vec3 *pt, glm::vec3 *dir = NULL);
      void debug();
      float smoothstep(float edge0, float edge1, float x);
      float spikeball(glm::vec3 p, float t);
   private:
      float rad;
};

#endif
