#include "geom/wavy.h"
#include "geom/transform.h"

using namespace glm;

Wavy::Wavy()
{
   coefficients = vec4(0.f);
}

Wavy::Wavy(vec4 _coefficients) :
   coefficients(_coefficients)
{
   coefficients = normalize(coefficients);
}

float Wavy::dist(vec3 *pt)
{
   return sin(pt->z);
}

vec3 Wavy::getNormal(vec3 *pt)
{
   // TODO: Make this involve transforms.
   vec3 d = vec3(coefficients);
   return d;
}

void Wavy::debug()
{
   printf("Wavy\n");
}
