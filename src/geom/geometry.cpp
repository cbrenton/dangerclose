#include "geom/geometry.h"
#include "geom/transform.h"

using namespace glm;

Geometry::~Geometry()
{
}

float Geometry::dist(vec3 *pt)
{
   return 0.f;
}

vec3 Geometry::getColor(vec3 *pt)
{
   return color;
}

void Geometry::setColor(vec3 c)
{
   color = c;
}

void Geometry::addTrans(Transform *t)
{
   trans.push_back(t);
}

vec3 Geometry::getNormal(vec3 *pt)
{
   return vec3();
}
