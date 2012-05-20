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

float Box::dist(vec3 *pt, vec3 *dir)
{
   return length(max(abs(*pt) - size, 0.0));
}

void Box::debug()
{
   printf("Box\n");
}
