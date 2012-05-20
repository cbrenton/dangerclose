#include "geom/sphere.h"
#include "geom/transform.h"

using namespace glm;

Sphere::Sphere(float _rad) :
   rad(_rad)
{
}

float Sphere::dist(vec3 *pt)
{
   return length(*pt) - rad;
}

void Sphere::debug()
{
   printf("Sphere {%f}\n", rad);
}
