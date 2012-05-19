#include "geom/translate.h"
#include "glm/glm.hpp"

using namespace glm;

Translate::Translate()
{
   // Initialize the transformation matrix to the identity matrix.
   transMat = mat4();
   transMat = inverse(transMat);
}

Translate::Translate(vec3 d)
{
   transMat = translate(mat4(), d);
   transMat = inverse(transMat);
}

float Translate::dist(vec3 *pt)
{
   vec3 m = vec3(transMat * vec4(*pt, 1.f));
   return prim->dist(&m);
}

void Translate::debug()
{
   printf("Translate: <%f, %f, %f>\n", inverse(transMat)[0][3], inverse(transMat)[1][3], inverse(transMat)[2][3]);
}
