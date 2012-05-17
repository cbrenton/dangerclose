#include "geom/translate.h"
#include "glm/glm.hpp"

using namespace glm;

Translate::Translate(Geometry *g) :
   Transform(g)
{
   // Initialize the transformation matrix to the identity matrix.
   transMat = mat4();
   transMat = inverse(transMat);
}

Translate::Translate(Geometry *g, vec3 d) :
   Transform(g)
{
   transMat = translate(mat4(), d);
   transMat = inverse(transMat);
}

float Translate::dist(vec3 *pt)
{
   vec3 m = vec3(transMat * vec4(*pt, 1.f));
   return prim->dist(&m);
}
