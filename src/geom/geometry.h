#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include <vector>
#include "glm/glm.hpp"

#define EPSILON 0.001f

#define mPR_VEC(a) printf("<%f, %f, %f>", (a).x, (a).y, (a).z)
#define mPRLN_VEC(a) printf("<%f, %f, %f>\n", (a).x, (a).y, (a).z)

class Transform;

class Geometry
{
   public:
      Geometry() {};
      virtual ~Geometry();
      virtual float getDist(glm::vec3 *pt);
      virtual float dist(glm::vec3 *pt);
      virtual glm::vec3 getColor(glm::vec3 *pt, int hopCount);
      virtual void setColor(glm::vec3 c);
      virtual void addTrans(Transform *t);
      virtual glm::vec3 getNormal(glm::vec3 *pt);
      virtual glm::vec3 cdNormal(glm::vec3 *pt);
      virtual void debug();
   protected:
      std::vector <Transform *> trans;
      glm::vec3 color;
};

#endif
