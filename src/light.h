/**
 * Light - not very heavy.
 * Sterling Hirsh
 * 4/5/11
 */

#ifndef _LIGHT_H
#define _LIGHT_H

#include <iostream>
#include <stdio.h>
#include "glm/glm.hpp"

class Light {
   public:
      Light(glm::vec3 _loc, glm::vec3 _color);
      glm::vec3 loc;
      glm::vec3 color;
      inline void debug()
      {
         printf("Light: (r,g,b) (%f, %f, %f)\n", color.x, color.y, color.z);
      }
};

#endif

