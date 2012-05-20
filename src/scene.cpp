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

float Scene::closestDist(vec3 *pt, float max, vec3 *colorOut, int hopCount)
{
   float closestD = max;
   vec3 color;
   if (gVec.size() == 0)
      return closestD;
   Geometry *closestPrim = gVec[0];
   for (int ndx = 0; ndx < (int)gVec.size(); ndx++)
   {
      float curDist = gVec[ndx]->getDist(pt);
      if (curDist < closestD && curDist >= 0.f)
      {
         closestD = curDist;
         closestPrim = gVec[ndx];
      }
   }
   color = closestPrim->getColor(pt, hopCount);
   *colorOut = color;
   return closestD;
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
