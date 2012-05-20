/**
 * Material class. Holds Phong coefficients (for now) and color values.
 * @author Chris Brenton
 * @date 2012/05/20
 */
#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "glm/glm.hpp"

class Material
{
   public:
      Material() {};
      Material(glm::vec4 _phong, glm::vec3 _color);
      Material(float _kA, float _kD, float _kS, float _rough, float _r,
            float _g, float _b);
      ~Material() {};
      float kA, kD, kS, rough;
      glm::vec3 color;
};

#endif
