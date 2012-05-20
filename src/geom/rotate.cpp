#include "geom/rotate.h"
#include "glm/glm.hpp"

using namespace glm;

Rotate::Rotate()
{
   // Initialize the transformation matrix to the identity matrix.
   transMat = mat4();
   transMat = inverse(transMat);
}

Rotate::Rotate(float angle, vec3 d)
{
   transMat = rotate(mat4(), angle, d);
   transMat = inverse(transMat);
}

float Rotate::dist(vec3 *pt, vec3 *dir)
{
   vec3 m = vec3(transMat * vec4(*pt, 1.f));
   if (dir == NULL)
   {
      return prim->dist(&m, dir);
   }
   vec3 mDir = vec3(transMat * vec4(*dir, 1.f));
   return prim->dist(&m, &mDir);
}

void Rotate::debug()
{
   printf("Rotate\n");
}
