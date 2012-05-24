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
   /*
      if (dir == NULL)
      {
      return dot(*pt, normal) - offset;
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
   //return dot(*pt, normal) - offset;
   */
   /*
   // TODO: Make this its own class. Put in wavy?
   float f1 = 10.0 * sin(pt->z * 0.125) * cos(pt->x * 0.125); // texture(uTex0, vPos.xz * 0.05).r; //
   float f2 = pt->y;
   const float fThickness = 0.0;
   return (f2 - f1) - fThickness;
   */
   return dot(*pt, normal) - offset;
}

void Plane::debug()
{
   printf("Plane:\n");
   printf("\tnormal: ");
   mPRLN_VEC(normal);
   printf("\toffset: %f\n", offset);
}
