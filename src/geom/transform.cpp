#include "geom/transform.h"

using namespace glm;

Transform::Transform(Geometry *g) :
   prim(g)
{
}

float Transform::dist(vec3 *pt)
{
   // TODO: Put this in Scale class.
   /*
   float s = 2.f;
   vec3 mod = *pt / s;
   return prim->dist(&mod) * s;
   */
   fprintf(stderr, "Transform::dist(). Should never be here.\n");
   exit(EXIT_FAILURE);
   return 0.f;
}

float Transform::pureDist(vec3 *pt)
{
   return dist(pt);
}

void Transform::debug()
{
   printf("Transform\n");
}
