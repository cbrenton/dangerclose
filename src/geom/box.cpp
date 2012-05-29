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
   /*
   vec3 di = abs(*pt) - *dir;
   float mc = mMAX_COMP(di);
   return std::min(mc, length(max(di, 0.0f)));
   */
}

void Box::debug()
{
   printf("Box\n");
}
