/**
 * Scale class.
 * This scales an object.
 * @author Chris Brenton
 * @date 2012/05/17
 */
#ifndef _SCALE_H
#define _SCALE_H

#include "geom/geometry.h"
#include "geom/transform.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include <stdio.h>

class Scale : public Transform
{
   public:
      Scale();
      Scale(glm::vec3 d);
      ~Scale() {};
      float dist(glm::vec3 *pt);
      void debug();
   private:
      glm::mat4 transMat;
};

#endif
