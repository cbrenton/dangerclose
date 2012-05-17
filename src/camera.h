/**
 * Camera class.
 * Adapted from Sterling Hirsh's Camera class.
 * @author Chris Brenton
 * @date 2012/05/10
 */

#ifndef _CAMERA_H
#define _CAMERA_H

#include <iostream>
#include "glm/glm.hpp"

class Camera {
   public:
      Camera() {};
      Camera(glm::vec3 _loc, glm::vec3 _up, glm::vec3 _right, glm::vec3 _look_at);
      ~Camera() {};
      glm::vec3 loc;
      glm::vec3 up;
      glm::vec3 right;
      glm::vec3 look_at;
};

#endif
