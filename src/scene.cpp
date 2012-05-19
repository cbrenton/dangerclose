#include "scene.h"

using namespace glm;

Scene::Scene()
{
   cam = new Camera();
}

Scene::Scene(std::vector<Geometry *> gVecIn) :
   gVec(gVecIn)
{
   cam = new Camera();
}

Scene::~Scene()
{
   for (int ndx = 0; ndx < (int)gVec.size(); ndx++)
   {
      delete gVec[ndx];
   }
   delete cam;
}

float Scene::closestDist(vec3 *pt, float max, vec3 *colorOut)
{
   float closest = max;
   vec3 color;
   for (int ndx = 0; ndx < (int)gVec.size(); ndx++)
   {
      float curDist = gVec[ndx]->getDist(pt);
      if (curDist < closest && curDist >= 0.f)
      {
         closest = curDist;
         color = gVec[ndx]->getColor(pt);
      }
   }
   *colorOut = color;
   return closest;
}

void Scene::addGeom(Geometry *g)
{
   gVec.push_back(g);
}

void Scene::setCam(Camera *c)
{
   cam = c;
}

Camera Scene::getCam()
{
   return *cam;
}
