/**
 * Ray class.
 * @author Chris Brenton
 * @date 2012/05/10
 */
#ifndef _RAY_H
#define _RAY_H

#include <stdio.h>
#include "glm/glm.hpp"

class Ray
{
   public:
      Ray();
      Ray(glm::vec3 _pt, glm::vec3 _dir);
      ~Ray() {};
      void debug();
      glm::vec3 pt;
      glm::vec3 dir;
};

#endif
