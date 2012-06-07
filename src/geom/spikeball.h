#ifndef _SPIKEBALL_H
#define _SPIKEBALL_H

#include "geom/geometry.h"

#define lerp(t, a, b) ( a + t * (b - a) )

class Spikeball : public Geometry
{
   public:
      Spikeball(float _rad);
      ~Spikeball() {};
      float dist(glm::vec3 *pt, glm::vec3 *dir = NULL);
      void debug();
      float smoothstep(float edge0, float edge1, float x);
   private:
      float rad;
};

#endif
