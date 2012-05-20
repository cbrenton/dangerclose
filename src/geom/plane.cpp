#include "geom/plane.h"
#include "geom/transform.h"

using namespace glm;

Plane::Plane()
{
   normal = vec3(0.f, 1.f, 0.f);
   offset = 0.f;
}

Plane::Plane(vec3 _normal, float _offset) :
   normal(_normal), offset(_offset)
{
   normal = normalize(normal);
}

float Plane::dist(vec3 *pt)
{
   return dot(*pt, normal + offset);
}

void Plane::debug()
{
   printf("Plane\n");
}
