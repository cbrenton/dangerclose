/**
 * Rotate class.
 * This rotates an object.
 * @author Chris Brenton
 * @date 2012/05/17
 */
#ifndef _ROTATE_H
#define _ROTATE_H

#include "geom/geometry.h"
#include "geom/transform.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include <stdio.h>

class Rotate : public Transform
{
   public:
      Rotate();
      Rotate(float angle, glm::vec3 d);
      ~Rotate() {};
      float dist(glm::vec3 *pt, glm::vec3 *dir = NULL);
      void debug();
   private:
      glm::mat4 transMat;
};

#endif
