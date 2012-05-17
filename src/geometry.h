#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include "glm/glm.hpp"

#define EPSILON 0.01f

inline float sdSphere(glm::vec3 p, float s)
{
   return glm::length(p)-s;
}

#endif
