#include "geom/sphere.h"
#include "geom/transform.h"

using namespace glm;

Sphere::Sphere(float _rad) :
   rad(_rad)
{
}

float Sphere::dist(vec3 *pt, vec3 *dir)
{
   //return length(*pt) - rad;
   float time = -length(*pt - vec3(0, 0, -14));
   return spikeball(*pt, time);
}

float Sphere::spikeball(vec3 p, float t)
{
   vec3 c[19]={vec3(1,0,0),vec3(0,1,0),vec3(0,0,1),vec3(.577,.577,.577),vec3(-.577,.577,.577),vec3(.577,-.577,.577),
      vec3(.577,.577,-.577),vec3(0,.357,.934),vec3(0,-.357,.934),vec3(.934,0,.357),vec3(-.934,0,.357),vec3(.357,.934,0),
      vec3(-.357,.934,0),vec3(0,.851,.526),vec3(0,-.851,.526),vec3(.526,0,.851),vec3(-.526,0,.851),vec3(.851,.526,0),
      vec3(-.851,.526,0)};

   float l = length(p);
   p = normalize(p);
   float b = 0;
   for (int i=3; i<19; i++)
      b=max(abs(dot(p, c[i])), b);
   b = 1 - acos(b - .01)/(acos(-1) * 0.5);
   b = smoothstep(.78f, 1.0f, b);
   return l-rad*pow(1.5,b*(1.-lerp(.1,2,sin(t*2)*.5+.5)*b));
}

float Sphere::smoothstep(float edge0, float edge1, float x)
{
   float t = clamp(((x - edge0) / (edge1 - edge0)), 0.0f, 1.0f);
   return t * t * (3.0f - 2.0f * t );
}

void Sphere::debug()
{
   printf("Sphere {%f}\n", rad);
}
