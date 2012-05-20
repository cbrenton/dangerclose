/**
 * Sterling Hirsh
 * Light Class
 * 4/3/11
 */

#include <cstdlib>
#include <string>
#include "light.h"

using namespace glm;

Light::Light(vec3 _loc, vec3 _color) :
   loc(_loc), color(_color)
{
}
