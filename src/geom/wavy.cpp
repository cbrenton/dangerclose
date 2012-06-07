#include "geom/wavy.h"
#include "geom/transform.h"

using namespace glm;

Wavy::Wavy(vec3 _normal, float _offset) :
   normal(_normal), offset(_offset)
{
   normal = normalize(normal);
   trans = mat4(1.f);
}

float Wavy::dist(vec3 *pt, vec3 *dir)
{
   return sin(pt->z);
}

void Wavy::debug()
{
   printf("Wavy\n");
}
