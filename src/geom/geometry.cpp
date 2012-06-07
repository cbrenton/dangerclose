#include "geom/geometry.h"
#include "geom/transform.h"
#include "scene.h"

using namespace glm;

Geometry::~Geometry()
{
}

float Geometry::getDist(vec3 *pt, vec3 *dir)
{
   /*
   // If the transform vector is not empty, find the getDistance through the
   // transforms.
   if (!trans.empty())
   {
   return (trans.back()->dist(pt, dir));
   }
   return dist(pt, dir);
   */
   //vec3 m = vec3(invTrans * vec4(*pt, 1.f));
   vec3 m = vec3(invTrans * vec4(*pt, 1.f));
   /*
      float spacing = 2.00f;
      m.x = mod((m.x), spacing) - spacing / 2.f;
      m.y = mod((m.y), spacing) - spacing / 2.f;
      m.z = mod((m.z), spacing) - spacing / 2.f;
      */
   if (dir == NULL)
   {
      float d1, d2;
      if (csg_sub)
      {
         d1 = csg_sub->dist(&m, dir);
         d2 = dist(&m, dir);
         return std::max(-d1, d2);
      }
      else
      {
         return dist(&m, dir);
      }

   }
   vec3 mDir = vec3(invTrans * vec4(*dir, 1.f));
   float d1, d2;
   if (csg_sub)
   {
      d1 = csg_sub->dist(&m, dir);
      d2 = dist(&m, dir);
      return std::max(-d1, d2);
   }
   else
   {
      return dist(&m, dir);
   }
}

float Geometry::dist(vec3 *pt, vec3 *dir)
{
   printf("Should never be here. You must have forgotten to add a dist() function to a Geometry subclass.\n");
   return 0.f;
}


/**
 * @param pt the point at which color is being calculated.
 * @param dir the direction of the view vector.
 * @param hopCount the number of steps taken in the ray marching algorithm.
 * @param lVec the vector of all lights in the current scene.
 * @returns the correct color at the specified point.
 */
vec3 Geometry::getColor(vec3 *pt, vec3 *dir, int hopCount,
      std::vector<Light *>lVec)
{
   vec3 result;
   if (lVec.empty())
   {
      fprintf(stderr, "Should not be here. You must have forgotten to add a light to the scene.\n");
      exit(EXIT_FAILURE);
   }

   // Ambient.
   result.x = mat.kA * mat.color.x;
   result.y = mat.kA * mat.color.y;
   result.z = mat.kA * mat.color.z;

   vec3 normal = getNormal(pt);

   for (int i = 0; i < (int)lVec.size(); i++)
   {
      Light *l = lVec[i];

      // Diffuse.
      vec3 light = normalize(l->loc - *pt);
      float nDotL = dot(normal, light);
      nDotL = std::min(nDotL, 1.0f);
      if (nDotL > 0.0f)
      {
         result.x += mat.kD * mat.color.x * nDotL * l->color.x;
         result.y += mat.kD * mat.color.y * nDotL * l->color.y;
         result.z += mat.kD * mat.color.z * nDotL * l->color.z;
      }

      // Specular.
      vec3 r = normalize(reflect(light, normal));
      vec3 v = normalize(*dir);
      float rDotV = dot(r, v);
      rDotV = std::max(rDotV, 0.0f);
      rDotV = (float)pow(rDotV, 1.0f / mat.rough);
      rDotV = std::min(rDotV, 1.0f);
      if (rDotV > 0.0f)
      {
         result.x += mat.kS * mat.color.x * rDotV * l->color.x;
         result.y += mat.kS * mat.color.y * rDotV * l->color.y;
         result.z += mat.kS * mat.color.z * rDotV * l->color.z;
      }
   }

   result = clamp(result, 0.0f, 1.0f);
   return result;
}

void Geometry::setColor(vec3 c)
{
   color = c;
}

void Geometry::setMat(Material m)
{
   mat = m;
}

/*
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
   */

void Geometry::addTranslate(vec3 d)
{
   if (d.x == 0.f && d.y == 0.f && d.z == 0.f)
      return;
   trans = translate(trans, d);
   invTrans = inverse(trans);
}

void Geometry::addRotate(float angle, vec3 d)
{
   trans = rotate(trans, angle, d);
   invTrans = inverse(trans);
}

void Geometry::addScale(vec3 d)
{
   trans = scale(trans, d);
   invTrans = inverse(trans);
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
