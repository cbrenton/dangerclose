#include "geom/plane.h"
#include "geom/transform.h"

using namespace glm;

Plane::Plane(vec3 _normal, float _offset) :
   normal(_normal), offset(_offset)
{
   normal = normalize(normal);
}

float Plane::dist(vec3 *pt, vec3 *dir)
{
   if (dir == NULL)
   {
      return dot(*pt, normal) + offset;
   }
   float denominator = dot(*dir, normal);
   if (denominator == 0.0)
   {
      return MAX_D;
   }
   vec3 p = normal * offset;
   vec3 pMinusL = p - *pt;
   float numerator = dot(pMinusL, normal);
   return numerator / denominator;
}

void Plane::debug()
{
   printf("Plane\n");
}
