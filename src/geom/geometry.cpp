#include "geom/geometry.h"
#include "geom/transform.h"
#include "scene.h"

using namespace glm;

Geometry::~Geometry()
{
}

float Geometry::getDist(vec3 *pt, vec3 *dir)
{
   // If the transform vector is not empty, find the getDistance through the
   // transforms.
   if (!trans.empty())
   {
      return (trans.back()->dist(pt, dir));
   }
   return dist(pt, dir);
}

float Geometry::dist(vec3 *pt, vec3 *dir)
{
   printf("Should never be here. You must have forgotten to add a dist() function to a Geometry subclass.\n");
   return 0.f;
}

vec3 Geometry::getColor(vec3 *pt, int hopCount, Light *l, float proximity)
{
   vec3 light;
   if (l == NULL)
   {
      fprintf(stderr, "Should not be here. You must have forgotten to add a light to the scene.\n");
      exit(EXIT_FAILURE);
   }
   light = normalize(l->loc - *pt);
   vec3 normal = getNormal(pt);
   float nDotL = dot(normal, light);
   if (nDotL > 1.0f || nDotL < 0.0f)
   {
      nDotL = mCLAMP(nDotL, 0.0f, 1.0f);
   }
   // TODO: Add actual lighting computations. Requires materials.
   //return nDotL * l->color;
   //return clamp(nDotL * mat.color, 0.0f, 1.0f);

   float occludeD = proximity;
   float scale = 2.0f;
   if (occludeD > scale)
   {
      /*
      if (dynamic_cast<Sphere *>(this) != NULL)
      {
         printf("Sphere occludeD: %f; ", occludeD);
         mPRLN_VEC(*pt);
      }
      */
      //return vec3(0.0f, 1.0f, 1.0f);
      //return nDotL * l->color;
      return mat.color;
      //return clamp(nDotL * mat.color, 0.0f, 1.0f);
      //occludeD = scale;
   }
   occludeD = mCLAMP(occludeD, 0.0f, scale);
   //printf("closest: %f\n", occludeD);
   float colorMag = occludeD / scale;
   //float colorMag = occludeD;
   colorMag = mCLAMP(colorMag, 0.0f, 1.0f);
   /*
      if (dynamic_cast<Plane *>(this) != NULL && colorMag != 1.0f)
      {
      printf("plane colorMag: %f\n", colorMag);
   //return vec3(0.0f, 1.0f, 0.0f);
   }
   */
   //printf("\tcolorMag: %f\n", colorMag);
   //return vec3(1.0f - colorMag);
   //return vec3(colorMag);
   return clamp(mat.color * colorMag, 0.0f, 1.0f);
   //return clamp(vec3(nDotL * colorMag), 0.0f, 1.0f);

   /*
      vec3 preOcclude = clamp(nDotL * mat.color, 0.0f, 1.0f);
      float maxHops = 15.f;
      preOcclude /= maxHops;
      preOcclude *= std::min(maxHops, (float)hopCount);
      return preOcclude;
      */
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
