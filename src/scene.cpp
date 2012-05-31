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
      vec3 n = closestPrim->getNormal(pt);
      if (noOccludeColorOut)
      {
         *noOccludeColorOut = *colorOut;
      }
      // TODO: Maybe fix this? I don't like it right now.
      //sss(pt, dir, closestPrim, lVec, colorOut);

      *colorOut *= ao(pt, &n, falloff, intensity);
      /*
         if (subsurf != 1.0f)
         {
      //printf("subsurf: %f\n", subsurf);
       *colorOut = vec3(1.0f, 0.0f, 0.0f);
      // *colorOut *= subsurf;
      }
      */
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
void Scene::sss(vec3 *pt, vec3 *dir, Geometry *prim, std::vector<Light *>lVec, vec3 *colorOut)
{
   int samples = 1;
   float depthScale = 1.0f;
   float intensity = 0.3f;
   vec3 newColor;
   // For number of samples:
   for (int i = 0; i < samples; i++)
   {
      // Jitter randomly.
      vec3 jitter = vec3((float)(rand() % 300) / 3000.f, (float)(rand() % 300) / 3000.f, (float)(rand() % 300) / 3000.f);
      vec3 newPt = *pt + jitter + *dir * depthScale;
      // Cast ray into surface.
      float dist = prim->getDist(&newPt);
      //printf("dist: %f\n", dist);
      // If new point is within object:
      //if (dist >= 0.0f && dist < 0.05f)
      if (dist >= 0.0f && dist < 0.005f)
      {
         // Find color at new point.
         float factor = std::min(1.0f, std::max(0.0f, dist));
         factor = pow(factor, 3);
         //factor /= 0.3;
         vec3 sampleColor = prim->getColor(&newPt, dir, 0, lVec);
         sampleColor *= factor;
         // Add new color to total color.
         newColor += sampleColor;
      }
      else
      {
         newColor += *colorOut;
      }
      // Else if new point is outside of object:
      /*
      vec3 newPt2 = *pt + *dir * depthScale;
      if (prim->getDist(&newPt2) > 0.05f)
      {
         //printf("dist: %f\n", dist);
         float factor = dist / 0.4f;
         // *colorOut = vec3(factor, 0.0f, 0.0f);
         vec3 sampleColor = vec3(factor, 0.0f, 0.0f);
         newColor += sampleColor;
      }
      */
   }
   // Divide color by number of samples.
   newColor /= (float)samples;
   newColor *= intensity;
   // Add color to colorOut.
   *colorOut += newColor;
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
