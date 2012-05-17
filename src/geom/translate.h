/**
 * Translate class.
 * This translates an object.
 * @author Chris Brenton
 * @date 2012/05/17
 */
#ifndef _TRANSLATE_H
#define _TRANSLATE_H

#include "geom/geometry.h"
#include "geom/transform.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

class Translate : public Transform
{
   public:
      Translate() {};
      Translate(Geometry *g);
      Translate(Geometry *g, glm::vec3 d);
      ~Translate() {};
      float dist(glm::vec3 *pt);
   private:
      glm::mat4 transMat;
};

#endif
