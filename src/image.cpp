#include "image.h"

using namespace glm;

Image::Image(int w, int h):
   width(w), height(h)
{
   init();
   filename = "./out.tga";
}

Image::Image(int w, int h, std::string name):
   width(w), height(h), filename(name)
{
   init();
}

Image::~Image()
{
   for (int i = 0; i < width; ++i) {
      delete[] data[i];
   }
   delete[] data;
}

void Image::init()
{
   if (width <= 0 || height <= 0)
   {
      fprintf(stderr, "Invalid image dimensions.\n");
      exit(EXIT_FAILURE);
   }
   data = new vec3*[width];
   for (int i = 0; i < width; ++i) {
      data[i] = new vec3[height];
      for (int j = 0; j < height; ++j) {
         data[i][j] = vec3(0, 0, 0);
      }
   }
}

void Image::setPixel(int x, int y, vec3 *pIn)
{
   data[x][y].x = pIn->x;
   data[x][y].y = pIn->y;
   data[x][y].z = pIn->z;
}

void Image::testPattern()
{
   for (int i = 0; i < width; i++)
   {
      for (int j = 0; j < height; j++)
      {
         // Write image data.
         float xStep = (float)i / (float)width;
         float yStep = (float)j / (float)height;
         float r = (float)(ceil(xStep * 10.0) / 10.0);
         float g = (float)(1.0 - ceil(yStep * 10.0) / 10.0);
         float b = (float)(1.0 - ceil(xStep * 10.0) / 10.0);
         vec3 testPixel = vec3(r, g, b);
         setPixel(i, j, &testPixel);
      }
   }
}

void Image::writeHeader(std::ofstream& out)
{
   out << '\0'
      << '\0'
      << '\2' // Uncompressed RGB
      << '\0' << '\0'
      << '\0' << '\0'
      << '\0'
      << '\0' << '\0' // X origin
      << '\0' << '\0' // Y origin
      << (char) (width & 0xFF)
      << (char) ((width >> 8) & 0xFF)
      << (char) (height & 0xFF)
      << (char) ((height >> 8) & 0xFF)
      << (char) 24 // 24 bit bitmap
      << '\0';
}

void Image::write()
{
   char *name = (char*)filename.c_str();
   std::ofstream myfile;
   myfile.open(name);
   if (!myfile)
   {
      fprintf(stderr, "Error: unable to open %s\n", name);
      exit(EXIT_FAILURE);
   }
   else
   {
      printf("Writing to file %s\n", name);
   }

   writeHeader(myfile);

   for (int i = 0; i < height; i++)
   {
      for (int j = 0; j < width; j++)
      {
         data[j][i] = clamp(data[j][i], 0.f, 1.f);
         myfile << (char)((int)(data[j][i].z * 255.f))
            << (char)((int)(data[j][i].y * 255.f))
            << (char)((int)(data[j][i].x * 255.f));
      }
   }

   printf("done\n");

   myfile.close();
}

