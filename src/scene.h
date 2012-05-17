/**
 * Scene class. This contains all geometry data, as well as intersection,
 * normal calculation, etc.
 * @author Chris Brenton
 * @date 2012/05/15
 */
#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include "camera.h"
#include "geom/geometry.h"
#include "glm/glm.hpp"

class Scene
{
   public:
      Scene();
      Scene(std::vector<Geometry *> gVecIn);
      ~Scene();
      //static Scene * read(std::string filename);
      float closestDist(glm::vec3 *pt, float max, glm::vec3 *colorOut);
      void addGeom(Geometry *g);
      void setCam(Camera *c);
      Camera getCam();
   private:
      std::vector<Geometry *> gVec;
      Camera *cam;
};

#endif