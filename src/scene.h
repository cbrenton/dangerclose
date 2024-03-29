/**
 * Scene class. This contains all geometry data, as well as intersection,
 * normal calculation, etc.
 * @author Chris Brenton
 * @date 2012/05/15
 */
#ifndef _SCENE_H
#define _SCENE_H

#include <fstream>
#include <vector>
#include "camera.h"
#include "light.h"
#include "geom/box.h"
#include "geom/geometry.h"
#include "geom/rotate.h"
#include "geom/plane.h"
#include "geom/scale.h"
#include "geom/sphere.h"
#include "geom/translate.h"
#include "geom/wavy.h"
#include "glm/glm.hpp"
#include "parse/nyuparser.h"

class Scene
{
   public:
      Scene();
      Scene(std::vector<Geometry *> gVecIn);
      ~Scene();
      static Scene * read(std::string filename, float offset = 0.f);
      float closest(glm::vec3 *pt);
      float closestDist(glm::vec3 *pt, glm::vec3 *dir, glm::vec3 *colorOut,
            glm::vec3 *noOccludeColorOut, int hopCount, float falloff = 0.0f,
            float intensity = 0.0f);
      float ao(glm::vec3 *pt, glm::vec3 *n, float falloff, float intensity);
      void sss(glm::vec3 *pt, glm::vec3 *dir, Geometry *prim,
            std::vector<Light *>l, glm::vec3 *colorOut);
      void addGeom(Geometry *g);
      void addLight(Light *l);
      void setCamera(Camera c);
      Camera getCamera();
   private:
      std::vector<Geometry *> gVec;
      Camera cam;
      std::vector<Light *>lVec;
};

#endif
