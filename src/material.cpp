#include "material.h"

using namespace glm;

Material::Material(vec4 _phong, vec3 _color) :
   color(_color)
{
   kA = _phong.x;
   kD = _phong.y;
   kS = _phong.z;
   rough = _phong.w;
}

Material::Material(float _kA, float _kD, float _kS, float _rough, float _r,
            float _g, float _b) :
   kA(_kA), kD(_kD), kS(_kS), rough(_rough)
{
   color = vec3(_r, _g, _b);
}
