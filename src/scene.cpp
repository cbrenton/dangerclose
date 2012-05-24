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
   for (int ndx = 0; ndx < (int)lVec.size(); ndx++)
   {
      delete lVec[ndx];
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
   printf("Using input file %s.\n", filename.c_str());
   p->parse(in, *ret);
   delete p;
   return ret;
}

/**
 * Simply finds the distance to the closest Geometry object in the Scene.
 * A Geometry object can be specified as a parameter. This object will be
 * ignored in the distance calculations. This will be useful for ambient
 * occlusion (I think).
 * @param pt the point from which distance is measured.
 * @param self the Geometry object being tested.
 * @return the distance to the closest object in the Scene.
 */
float Scene::closest(vec3 *pt, Geometry *self)
{
   float closestD = MAX_D;
   if (gVec.size() == 0)
      return closestD;
   for (int ndx = 0; ndx < (int)gVec.size(); ndx++)
   {
      if (gVec[ndx] != self)
      {
         float curDist = abs(gVec[ndx]->getDist(pt, NULL));
         if (curDist < closestD)
         {
            closestD = curDist;
         }
      }
   }
   return closestD;
}

float Scene::closestDist(vec3 *pt, vec3 *dir, vec3 *colorOut, vec3 *noOccludeColorOut, int hopCount)
{
   float closestD = MAX_D;
   if (gVec.size() == 0)
      return closestD;
   Geometry *closestPrim = gVec[0];
   for (int ndx = 0; ndx < (int)gVec.size(); ndx++)
   {
      float curDist = gVec[ndx]->getDist(pt, dir);
      // TODO: Tweak these variables?
      //if (curDist < closestD && curDist >= -EPSILON * 10000.f)
      if (curDist < closestD)
      {
         closestD = curDist;
         closestPrim = gVec[ndx];
      }
   }
   // TODO: Put this in main. Onlu calculate color if there is a hit.
   // TODO: Tweak these variables?
   //if (abs(closestD) <= EPSILON * 10000.f)
   //{
      float proximity = closest(pt, closestPrim);
      *colorOut = closestPrim->getColor(pt, dir, hopCount, lVec, proximity, noOccludeColorOut);
   //}
   return closestD;
}

void Scene::addGeom(Geometry *g)
{
   gVec.push_back(g);
}

void Scene::addLight(Light *l)
{
   lVec.push_back(l);
}

void Scene::setCamera(Camera c)
{
   cam = c;
}

Camera Scene::getCamera()
{
   return cam;
}
