#include "geom/plane.h"
#include "geom/transform.h"

using namespace glm;

Plane::Plane()
{
   coefficients = vec4(0.f);
}

Plane::Plane(vec4 _coefficients) :
   coefficients(_coefficients)
{
   coefficients = normalize(coefficients);
}

float Plane::dist(vec3 *pt)
{
   //return dot(*pt, vec3(coefficients)) + coefficients.w;
   return dot(*pt, vec3(coefficients.x, coefficients.y, coefficients.z)) + coefficients.w;
}

vec3 Plane::getNormal(vec3 *pt)
{
   // TODO: Make this involve transforms.
   vec3 d = *pt;
   return d;
}

void Plane::debug()
{
   printf("Plane\n");
}
