#include "ray.h"

using namespace glm;

Ray::Ray()
{
   pt = vec3(0.0, 0.0, 0.0);
   dir = vec3(0.0, 0.0, 1.0);
}

Ray::Ray(vec3 _pt, vec3 _dir) :
   pt(_pt), dir(_dir)
{
}

void Ray::debug()
{
   printf("ray: [(%f, %f, %f)->(%f, %f, %f)]\n", pt.x, pt.y, pt.z, dir.x, dir.y, dir.z);
}
