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
#define DEFAULT_FALLOFF 0.0f
#define DEFAULT_INTENSITY 0.0f
#define DEFAULT_FILENAME "out.png"

#define INPUT_EXT ".pov"

using namespace glm;

int width = DEFAULT_W;
int height = DEFAULT_H;
float falloff = DEFAULT_FALLOFF;
float intensity = DEFAULT_INTENSITY;
std::string inputFileName;
std::string filename, noOccludeFilename;
Scene *scene;

void setWidth(char* strIn);
void setHeight(char* strIn);
void setFalloff(char* strIn);
void setIntensity(char* strIn);
void setFilename(char* strIn);
float r2d(float rads);
void initScene();

int main(int argc, char **argv)
{
   srand((int)time(NULL));

   int c;
   while ((c = getopt(argc, argv, "f:F:i:I:h:H:p:P:w:W:")) != -1)
   {
      switch (c)
      {
      // "Falloff" (ambient occlusion).
      case 'f': case 'F':
         setFalloff(optarg);
         break;
      // "Height".
      case 'h': case 'H':
         setHeight(optarg);
         break;
      // "Input file".
      case 'i': case 'I':
         setFilename(optarg);
         break;
      // "Power"/intensity (ambient occlusion).
      case 'p': case 'P':
         setIntensity(optarg);
         break;
      // "Width".
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
   Image noOccludeImg(width, height, noOccludeFilename);

   // Initialize scene.
   initScene();

   Ray ***aRayArray = new Ray **[width];
   for (int i = 0; i < width; i++)
   {
      aRayArray[i] = new Ray*[height];
   }

   Camera cam = scene->getCamera();

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
      printf("\r%d / %d", x, width);
      fflush(stdout);
      for (int y = 0; y < height; y++)
      {
         // Test for intersection.
         vec3 ray = aRayArray[x][y]->pt;
         vec3 rayDir = aRayArray[x][y]->dir;
         bool hit = false;
         vec3 *hitColor = new vec3;
         vec3 *noOccludeColor = new vec3;
         float rayDist = distance(aRayArray[x][y]->pt, ray);
         int hops = 0;
         while (!hit && rayDist < MAX_D)
         {
            // Check distance to sphere.
            float d = scene->closestDist(&ray, &rayDir, hitColor,
                  noOccludeColor, hops, falloff, intensity);
            // If distance is within epsilon, count as a hit.
            if (abs(d) <= EPSILON)
            {
               hit = true;
            }
            // If not a hit, advance ray by distance.
            else
            {
               ray += rayDir * d;
               rayDist = distance(rayDir, ray);
               hops++;
            }
         }
         if (hit)
         {
            img.setPixel(x, y, hitColor);
            noOccludeImg.setPixel(x, y, noOccludeColor);
         }
         delete hitColor;
         delete noOccludeColor;
      }
   }
   printf("\n");

   // Write image out to file.
   img.write();
   noOccludeImg.write();
   
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

void setFalloff(char* strIn)
{
   falloff = atof(strIn);
   if (height <= 0)
   {
      fprintf(stderr, "Invalid falloff.\n");
      exit(EXIT_FAILURE);
   }
}

void setIntensity(char* strIn)
{
   intensity = atof(strIn);
   if (height <= 0.0f)
   {
      fprintf(stderr, "Invalid intensity.\n");
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
   noOccludeFilename = filename;;
   noOccludeFilename.append("_no_occlude");
   filename.append(".tga");
   noOccludeFilename.append(".tga");
}

float r2d(float rads)
{
   return (float)(rads * 180 / M_PI);
}

void initScene()
{
   scene = Scene::read(inputFileName.c_str());
}
