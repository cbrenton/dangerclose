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

vec3 Geometry::getColor(vec3 *pt, int hopCount, Light *l)
{
   vec3 light;
   if (l == NULL)
   {
      fprintf(stderr, "Should not be here. You must have forgotten to add a light to the scene.\n");
      exit(EXIT_FAILURE);
   }
   light = normalize(l->loc - *pt);
   float nDotL = dot(cdNormal(pt), light);
   if (nDotL > 1.0f || nDotL < 0.0f)
   {
      mCLAMP(nDotL, 0.0f, 1.0f);
   }
   // TODO: Add actual lighting computations. Requires materials.
   //return nDotL * l->color;
   return nDotL * mat.color;
}

void Geometry::setColor(vec3 c)
{
   color = c;
}

void Geometry::setMat(Material m)
{
   mat = m;
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

vec3 Geometry::cdNormal(vec3 *pt)
{
   vec3 eps = vec3(EPSILON * 100.f, 0.0, 0.0);
   vec3 nor;
   vec3 pos = *pt;

   vec3 pt1 = (pos+vec3(eps.x, eps.y, eps.y));
   vec3 pt2 = (pos-vec3(eps.x, eps.y, eps.y));
   vec3 pt3 = (pos+vec3(eps.y, eps.x, eps.y));
   vec3 pt4 = (pos-vec3(eps.y, eps.x, eps.y));
   vec3 pt5 = (pos+vec3(eps.y, eps.y, eps.x));
   vec3 pt6 = (pos-vec3(eps.y, eps.y, eps.x));

   nor.x = getDist(&pt1) - getDist(&pt2);
   nor.y = getDist(&pt3) - getDist(&pt4);
   nor.z = getDist(&pt5) - getDist(&pt6);

   return normalize(nor);
}

void Geometry::debug()
{
   printf("Geometry\n");
}
