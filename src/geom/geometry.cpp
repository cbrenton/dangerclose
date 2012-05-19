#include "geom/geometry.h"
#include "geom/transform.h"

using namespace glm;

Geometry::~Geometry()
{
}

float Geometry::getDist(vec3 *pt)
{
   // If the transform vector is not empty, find the getDistance through the
   // transforms.
   if (!trans.empty())
   {
      return (trans.back()->dist(pt));
   }
   return dist(pt);
}

float Geometry::dist(vec3 *pt)
{
   printf("Should never be here. You must have forgotten to add a dist() function to a Geometry subclass.\n");
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
   if (trans.empty())
   {
      t->setPrim(this);
   }
   else
   {
      t->setPrim(trans.back());
   }
   trans.push_back(t);
}

vec3 Geometry::getNormal(vec3 *pt)
{
   return vec3();
}

void Geometry::debug()
{
   printf("Geometry\n");
}
