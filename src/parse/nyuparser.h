#ifndef NYUPARSER_H
#define NYUPARSER_H

#include "geom/geometry.h"
#include "geom/transform.h"
#include "glm/glm.hpp"
#include "parse/tokens.h"

class Scene;
class Camera;
class Box;
class Plane;
class Sphere;

class NYUParser{
   private:
      Tokenizer * tokenizer;

      // helper functions
      void ParseLeftAngle();
      void ParseRightAngle();
      double ParseDouble();
      void ParseLeftCurly();
      void ParseRightCurly();
      void ParseComma();
      void ParseVector(glm::vec3 & v);
      void ParseRGBFColor(glm::vec3 & c, float & f);
      void ParseRGBColor(glm::vec3 & c, float & f);
      void ParseColor(glm::vec3 & c, float & f);
      void PrintColor(glm::vec3 & c, float & f);
      void ParseMatrix();
      void ParseTransform(Geometry & s);
      void ParsePigment(Material & p);
      void PrintPigment(Material & p);
      void ParseFinish(Material & f);
      void PrintFinish(Material & f);
      // void ParseInterior( struct Interior* interior);
      void ParseInterior(float & ior);
      // void InitModifiers(struct ModifierStruct* modifiers);
      // void ParseModifiers(struct ModifierStruct* modifiers);
      // void PrintModifiers(struct ModifierStruct* modifiers);
      void ParseSubtract(Geometry & s);
      void ParseIntersect(Geometry & s);
      void ParseUnion(Geometry & s);
      void ParseModifiers(Geometry & s);
      void PrintModifiers(Geometry & s);
      Camera ParseCamera();
      Sphere * ParseSphere();
      Box * ParseBox();
      void ParseCylinder();
      // Cone * ParseCone();
      Plane * ParsePlane(); // added by mbecker
      Light * ParseLightSource();
      void ParseGlobalSettings();

   public:
      void parse(std::fstream & input, Scene & s);
      // Parse(FILE* infile);
};

#endif
