#include <cstdlib>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>
#include "camera.h"
#include "image.h"
#include "ray.h"
#include "scene.h"
#include "glm/glm.hpp"

#define DEFAULT_W 256
#define DEFAULT_H 256
#define DEFAULT_FILENAME "out.png"

#define INPUT_EXT ".pov"

using namespace glm;

int width = DEFAULT_W;
int height = DEFAULT_H;
std::string inputFileName;
std::string filename;
Scene *scene;

void setWidth(char* strIn);
void setHeight(char* strIn);
void setFilename(char* strIn);
float r2d(float rads);
void initScene();

int main(int argc, char **argv)
{
   srand((int)time(NULL));

   int c;
   while ((c = getopt(argc, argv, "i:I:h:H:w:W:")) != -1)
   {
      switch (c)
      {
      case 'h': case 'H':
         setHeight(optarg);
         break;
      case 'i': case 'I':
         setFilename(optarg);
         break;
      case 'w': case 'W':
         setWidth(optarg);
         break;
      default:
         fprintf(stderr, "Invalid command-line argument: %c\n", c);
         exit(EXIT_FAILURE);
         break;
      }
   }

   // TODO: Initialize image.
   Image img(width, height, filename);

   // Initialize scene.
   initScene();

   Ray ***aRayArray = new Ray **[width];
   for (int i = 0; i < width; i++)
   {
      aRayArray[i] = new Ray*[height];
   }

   Camera cam = scene->getCam();

   float l = -length(cam.right) / 2.0f;
   float r = length(cam.right) / 2.0f;
   float b = -length(cam.up) / 2.0f;
   float t = length(cam.up) / 2.0f;

   // Generate rays.
   printf("Generating rays...");
   for (int x = 0; x < width; x++)
   {
      for (int y = 0; y < height; y++)
      {
         float jitter = 0.5f;

         float uScale = (float)(l + (r - l) * ((float)x + jitter)
               / (float)width);
         float vScale = (float)(b + (t - b) * ((float)y + jitter)
               / (float)height);
         float wScale = -1;
         vec3 sVector = cam.loc;
         vec3 uVector = cam.right;
         vec3 vVector = cam.up;
         vec3 wVector = cam.look_at - cam.loc;
         normalize(uVector);
         normalize(vVector);
         normalize(wVector);
         // Left-handed.
         wVector *= -1;
         uVector *= uScale;
         vVector *= vScale;
         wVector *= wScale;
         sVector += uVector;
         sVector += vVector;
         sVector += wVector;
         vec3 rayDir = uVector + vVector + wVector;
         rayDir = normalize(rayDir);
         vec3 curPoint = cam.loc;
         Ray *curRay = new Ray(curPoint, rayDir);
         aRayArray[x][y] = curRay;
      }
   }
   printf("done.\n");
   
   printf("Testing intersections.\n");
   for (int x = 0; x < width; x++)
   {
      for (int y = 0; y < height; y++)
      {
         // Test for intersection.
         float maxLen = 100.0f;
         vec3 ray = aRayArray[x][y]->pt;
         bool hit = false;
         vec3 *hitColor = new vec3;
         float rayDist = distance(aRayArray[x][y]->pt, ray);
         int hops = 0;
         while (!hit && rayDist < maxLen)
         {
            // Check distance to sphere.
            float d = scene->closestDist(&ray, maxLen, hitColor, hops);
            // If distance is less than or equal to epsilon, count as a hit.
            if (d <= EPSILON)
            {
               hit = true;
            }
            // If not a hit, advance ray by distance.
            else
            {
               ray += aRayArray[x][y]->dir * d;
               rayDist = distance(aRayArray[x][y]->pt, ray);
               hops++;
            }
         }
         if (hit)
         {
            img.setPixel(x, y, hitColor);
         }
      }
   }

   // Write image out to file.
   img.write();
   
   // Cleanup.
   for (int i = 0; i < width; i++)
   {
      for (int j = 0; j < height; j++)
      {
         delete aRayArray[i][j];
      }
      delete[] aRayArray[i];
   }
   delete[] aRayArray;

   delete scene;
   
   return EXIT_SUCCESS;
}

void setWidth(char* strIn)
{
   width = atoi(strIn);
   if (width <= 0)
   {
      fprintf(stderr, "Invalid width.\n");
      exit(EXIT_FAILURE);
   }
}

void setHeight(char* strIn)
{
   height = atoi(strIn);
   if (height <= 0)
   {
      fprintf(stderr, "Invalid height.\n");
      exit(EXIT_FAILURE);
   }
}

void setFilename(char* strIn)
{
   std::string name = "";
   if (strIn[0] == '=')
   {
      name = strIn[1];
   }
   else
   {
      name = strIn;
   }
   inputFileName = name;
   int dirIndex = (int)inputFileName.rfind('/');
   int extIndex = (int)inputFileName.rfind(INPUT_EXT);
   filename = "images/";
   filename.append(inputFileName.substr(dirIndex + 1, extIndex - dirIndex - 1));
   filename.append(".tga");
}

float r2d(float rads)
{
   return (float)(rads * 180 / M_PI);
}

void initScene()
{
   // Camera definition.
   vec3 right = vec3(1.0f, 0.0f, 0.0f);
   vec3 up = vec3(0.0f, 1.0f, 0.0f);
   vec3 loc = vec3(0.0f, 0.0f, -10.0f);
   vec3 look_at = vec3(0.0f, 0.0f, 0.0f);
   Camera *cam = new Camera(loc, up, right, look_at);
   // Geometry definitions.
   Sphere *sp = new Sphere(0.1f);
   sp->setColor(vec3(1.0f, 0.0f, 0.0f));
   Sphere *sp2 = new Sphere(0.1f);
   sp2->setColor(vec3(0.0f, 1.0f, 0.0f));
   Box *b = new Box(0.075f);
   b->setColor(vec3(0.0f, 0.0f, 1.0f));
   Plane *p = new Plane(vec4(0.0f, 1.0f, 0.0f, 1.0f));
   p->setColor(vec3(1.0f, 0.0f, 1.0f));
   //Wavy *w = new Wavy();
   //w->setColor(vec3(0.0f, 1.0f, 1.0f));
   // Transform definitions.
   Translate *myTranslate = new Translate(vec3(0.1f, 0.0f, -1.6f));
   Rotate *myRotate = new Rotate(10.0f, vec3(0.0f, 1.0f, 0.0f));
   Rotate *myRotate2 = new Rotate(15.0f, vec3(0.0f, 1.0f, 0.0f));
   Rotate *myRotate3 = new Rotate(30.0f, vec3(0.0f, 0.0f, 1.0f));
   Scale *myScale = new Scale(vec3(0.8f, 2.0f, 1.0f));
   sp->addTrans(myTranslate);
   sp->addTrans(myRotate);
   b->addTrans(myScale);
   b->addTrans(myRotate2);
   b->addTrans(myRotate3);
   // Scene definition.
   scene = new Scene();
   scene->setCam(cam);
   scene->addGeom(sp);
   scene->addGeom(sp2);
   scene->addGeom(b);
   scene->addGeom(p);
   //scene->addGeom(w);
}
