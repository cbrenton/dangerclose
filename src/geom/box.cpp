#include "geom/box.h"
#include "geom/transform.h"

using namespace glm;

Box::Box()
{
   size = 0.f;
}

Box::Box(float _size) :
   size(_size)
{
}

float Box::dist(vec3 *pt)
{
   return length(max(abs(*pt) - size, 0.0));
}

vec3 Box::getNormal(vec3 *pt)
{
   // TODO: Make this involve transforms.
   vec3 d = *pt;
   return d;
}

void Box::debug()
{
   printf("Box\n");
}
