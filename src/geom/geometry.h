#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include <vector>
#include "glm/glm.hpp"
#include "light.h"
#include "material.h"

#define EPSILON 0.001f
#define MAX_D 1000.f

#define mPR_VEC(a) printf("<%f, %f, %f>", (a).x, (a).y, (a).z)
#define mPRLN_VEC(a) printf("<%f, %f, %f>\n", (a).x, (a).y, (a).z)
#define mCLAMP(a, small, large) (std::min(std::max((a), (small)), (large)))

class Transform;

class Scene;

class Geometry
{
   public:
      Geometry() {};
      virtual ~Geometry();
      virtual float getDist(glm::vec3 *pt, glm::vec3 *dir = NULL);
      virtual float dist(glm::vec3 *pt, glm::vec3 *dir = NULL);
      virtual glm::vec3 getColor(glm::vec3 *pt, glm::vec3 *dir, int hopCount,
            std::vector<Light *>l);
      virtual void setColor(glm::vec3 c);
      virtual void setMat(Material m);
      //virtual void addTrans(Transform *t);
      virtual void addTranslate(glm::vec3 d);
      virtual void addRotate(float angle, glm::vec3 d);
      virtual void addScale(glm::vec3 d);
      virtual glm::vec3 getNormal(glm::vec3 *pt);
      virtual void debug();
      Material mat;
   protected:
      //std::vector <Transform *> trans;
      glm::vec3 color;
      glm::mat4 trans;
      glm::mat4 invTrans;
      Scene *parent;
};

#endif
