#include "geom/sphere.h"
#include "geom/transform.h"

using namespace glm;

Sphere::Sphere()
{
   rad = 0.f;
}

Sphere::Sphere(float _rad) :
   rad(_rad)
{
}

float Sphere::dist(vec3 *pt)
{
   // TODO: Clean this shit up.
   if (!trans.empty())
   {
      return (trans[0]->dist(pt));
   }
   return length(*pt) - rad;
}

float Sphere::dist(vec3 &pt)
{
   return length(pt) - rad;
}

vec3 Sphere::getNormal(vec3 *pt)
{
   // TODO: Make this involve transforms.
   vec3 d = *pt;
   return d;
}
