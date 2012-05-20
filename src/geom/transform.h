#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "geom/geometry.h"
#include "glm/glm.hpp"

class Transform : public Geometry
{
   public:
      Transform() {};
      Transform(Geometry *g);
      virtual ~Transform() {};
      virtual float dist(glm::vec3 *pt, glm::vec3 *dir = NULL);
      void setPrim(Geometry *g);
      virtual void debug();
   protected:
      Geometry * prim;
};

#endif
