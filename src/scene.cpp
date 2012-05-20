#include "scene.h"

using namespace glm;

Scene::Scene()
{
   cam = Camera();
}

Scene::Scene(std::vector<Geometry *> gVecIn) :
   gVec(gVecIn)
{
   cam = Camera();
}

Scene::~Scene()
{
   for (int ndx = 0; ndx < (int)gVec.size(); ndx++)
   {
      delete gVec[ndx];
   }
}

Scene * Scene::read(std::string filename)
{
   Scene *ret = new Scene();
   NYUParser *p = new NYUParser();
   std::fstream in(filename.c_str());
   if (!in)
   {
      fprintf(stderr, "Invalid input file: %s\n", filename.c_str());
      exit(EXIT_FAILURE);
   }
   p->parse(in, *ret);
   delete p;
   return ret;
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
   color = closestPrim->getColor(pt, hopCount, light);
   *colorOut = color;
   return closestD;
}

void Scene::addGeom(Geometry *g)
{
   gVec.push_back(g);
}

void Scene::addLight(Light *l)
{
   light = l;
}

void Scene::setCamera(Camera c)
{
   cam = c;
}

Camera Scene::getCamera()
{
   return cam;
}
