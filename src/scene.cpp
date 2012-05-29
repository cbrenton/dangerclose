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
float Scene::closest(vec3 *pt)
{
   float closestD = MAX_D;
   if (gVec.size() == 0)
      return closestD;
   for (int ndx = 0; ndx < (int)gVec.size(); ndx++)
   {
      float curDist = abs(gVec[ndx]->getDist(pt, NULL));
      if (curDist < closestD)
      {
         closestD = curDist;
      }
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
   if (abs(closestD) <= EPSILON)
   {
      *colorOut = closestPrim->getColor(pt, dir, hopCount, lVec);
      //vec3 n = closestPrim->getNormal(pt);
      if (noOccludeColorOut)
      {
         *noOccludeColorOut = *colorOut;
      }
      //*colorOut *= ao(pt, &n, falloff, intensity);
      //*colorOut *= vec3(sss(pt, dir, 0.0f, 0.0f, closestPrim));
      float subsurf = sss(pt, dir, 0.0f, 0.0f, closestPrim);
      if (subsurf != 1.0f)
      {
         //printf("subsurf: %f\n", subsurf);
         //*colorOut = vec3(1.0f, 0.0f, 0.0f);
         *colorOut *= subsurf;
      }
   }
   return closestD;
}

/**
 * Calculates object-space ambient occlusion.
 * @param pt the point at which occlusion is being calculated.
 * @param n the normal at the specified point.
 * @param falloff the distance at which there will be no occlusion.
 * @param intensity the maximum contribution value of ambient occlusion.
 * @returns the coefficient of ambient occlusion.
 */
float Scene::ao(glm::vec3 *pt, glm::vec3 *n, float falloff, float intensity)
{
   vec3 offset = *pt + *n;
   float proximity = closest(&offset);
   if (proximity <= falloff)
   {
      proximity = mCLAMP(proximity, 0.0f, falloff);
      float colorMag = proximity / falloff;
      colorMag = colorMag * intensity + (1.0f - intensity);
      //result *= colorMag;
      return colorMag;
      // TODO: Make this better.
      //float bleedIntensity = (1.0f - colorMag) * mat.kS;
      // *bleed *= bleedIntensity;
      //result += *bleed;
   }
   return 1.0f;
}

/**
 * Calculate subsurface scattering at a given point.
 * @param pt the point at which occlusion is being calculated.
 * @param n the direction of the view ray.
 * @param d who knows?
 * @param i hop count, I think?
 * @param prim the Geometry object the original point is located on.
 * @returns the coefficient of subsurface scattering.
 */
float Scene::sss(vec3 *pt, vec3 *dir, float d, float i, Geometry *prim)
{
   vec3 offset = *pt + *dir * 0.5f;
   //float proximity = closest(&offset);
   float proximity = prim->getDist(&offset);
   if (proximity > 0.0f)
   {
      //printf("sss proximity: %f\n", proximity);
      return 1.0f + proximity * 3.0f;
   }
   /*
   if (proximity <= falloff)
   {
      proximity = mCLAMP(proximity, 0.0f, falloff);
      float colorMag = proximity / falloff;
      colorMag = colorMag * intensity + (1.0f - intensity);
      return colorMag;
   }
   */
   return 1.0f;
   /*
   float o;
   for (o=0.f;i>0.f;i--) {
      vec3 newPt = vec3(*pt + *n * i * d);
      float f = prim->getDist(&newPt);
      o+=(i*d+f)/exp2(i);
   }
   return o;
   */
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
