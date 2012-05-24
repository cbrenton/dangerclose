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
float Scene::closest(vec3 *pt, vec3 *color)
{
   float closestD = MAX_D;
   if (gVec.size() == 0)
      return closestD;
   int closeNdx = 0;
   for (int ndx = 0; ndx < (int)gVec.size(); ndx++)
   {
      float curDist = abs(gVec[ndx]->getDist(pt, NULL));
      if (curDist < closestD)
      {
         closestD = curDist;
         closeNdx = ndx;
      }
   }
   if (color != NULL)
   {
      *color = gVec[closeNdx]->mat.color * 0.3f;
   }
   return closestD;
}

float Scene::closestDist(vec3 *pt, vec3 *dir, vec3 *colorOut,
      vec3 *noOccludeColorOut, int hopCount, float falloff, float intensity)
{
   float closestD = MAX_D;
   if (gVec.size() == 0)
      return closestD;
   Geometry *closestPrim = gVec[0];
   for (int ndx = 0; ndx < (int)gVec.size(); ndx++)
   {
      float curDist = gVec[ndx]->getDist(pt, dir);
      if (curDist < closestD)
      {
         closestD = curDist;
         closestPrim = gVec[ndx];
      }
   }
   vec3 normal = closestPrim->getNormal(pt);
   vec3 offset = *pt + normal;
   vec3 bleed;
   float proximity = closest(&offset, &bleed);
   *colorOut = closestPrim->getColor(pt, dir, hopCount, lVec, proximity,
         falloff, intensity, noOccludeColorOut, &bleed);
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
