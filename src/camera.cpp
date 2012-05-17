/**
 * Camera class.
 * @author Chris Brenton
 * @date 2012/05/10
 */

#include "camera.h"

using namespace glm;

Camera::Camera(vec3 _loc, vec3 _up, vec3 _right, vec3 _look_at) :
   loc(_loc), up(_up), right(_right), look_at(_look_at)
{
}
