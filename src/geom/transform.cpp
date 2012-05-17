#include "geom/transform.h"

using namespace glm;

Transform::Transform(Geometry *g) :
   prim(g)
{
}

float Transform::dist(vec3 *pt)
{
   float s = 2.f;
   vec3 mod = *pt / s;
   return prim->dist(&mod) * s;
}
