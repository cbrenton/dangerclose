#include "geom/sphere.h"
#include "geom/transform.h"

using namespace glm;

Sphere::Sphere(float _rad) :
   rad(_rad)
{
   trans = mat4(1.f);
}

float Sphere::dist(vec3 *pt, vec3 *dir)
{
   return length(*pt) - rad;
}

void Sphere::debug()
{
   printf("Sphere {%f}\n", rad);
}
