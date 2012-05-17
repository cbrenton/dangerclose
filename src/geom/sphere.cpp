#include "geom/sphere.h"

using namespace glm;

Sphere::Sphere()
{
   rad = 0.f;
}

Sphere::Sphere(float _rad) :
   rad(_rad)
{
}

/*
float Sphere::transDist(vec3 *pt)
{
   float s = 2.f;
   vec3 mod = *pt / s;
   //mat4 m = rotate(mat4(1.f), 45.0, vec3(1.f, 0.f, 0.f));
   return dist(&mod) * s;
}
*/

float Sphere::dist(vec3 *pt)
{
   return length(*pt) - rad;
}

float Sphere::dist(vec3 &pt)
{
   return length(pt) - rad;
}
