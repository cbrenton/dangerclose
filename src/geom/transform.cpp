#include "geom/transform.h"

using namespace glm;

Transform::Transform(Geometry *g) :
   prim(g)
{
}

float Transform::dist(vec3 *pt)
{
   return 0.f;
}

void Transform::setPrim(Geometry *g)
{
   prim = g;
}

void Transform::debug()
{
   printf("Transform\n");
}
