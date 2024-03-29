#include "geom/scale.h"
#include "glm/glm.hpp"

using namespace glm;

Scale::Scale()
{
   // Initialize the transformation matrix to the identity matrix.
   transMat = mat4();
   transMat = inverse(transMat);
}

Scale::Scale(vec3 d)
{
   transMat = scale(mat4(), d);
   transMat = inverse(transMat);
}

float Scale::dist(vec3 *pt, vec3 *dir)
{
   vec3 m = vec3(transMat * vec4(*pt, 1.f));
   if (dir == NULL)
   {
      return prim->dist(&m, dir);
   }
   vec3 mDir = vec3(transMat * vec4(*dir, 1.f));
   return prim->dist(&m, &mDir);
}

void Scale::debug()
{
   printf("Scale\n");
}
