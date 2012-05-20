#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include <vector>
#include "glm/glm.hpp"
#include "light.h"
#include "material.h"

#define EPSILON 0.0001f

#define mPR_VEC(a) printf("<%f, %f, %f>", (a).x, (a).y, (a).z)
#define mPRLN_VEC(a) printf("<%f, %f, %f>\n", (a).x, (a).y, (a).z)
#define mCLAMP(a, small, large) ((a) = std::min(std::max((a), (small)), (large)))

class Transform;

class Geometry
{
   public:
      Geometry() {};
      virtual ~Geometry();
      virtual float getDist(glm::vec3 *pt);
      virtual float dist(glm::vec3 *pt);
      virtual glm::vec3 getColor(glm::vec3 *pt, int hopCount, Light *l);
      virtual void setColor(glm::vec3 c);
      virtual void setMat(Material m);
      virtual void addTrans(Transform *t);
      virtual glm::vec3 getNormal(glm::vec3 *pt);
      virtual glm::vec3 cdNormal(glm::vec3 *pt);
      virtual void debug();
      Material mat;
   protected:
      std::vector <Transform *> trans;
      glm::vec3 color;
};

#endif
