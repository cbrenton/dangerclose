#ifndef _IMAGE_H
#define _IMAGE_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "glm/glm.hpp"

class Image {
   public:
      Image() {};
      Image(int w, int h);
      Image(int w, int h, std::string name);
      ~Image();
      glm::vec3 **data;
      void setSize(int w, int h);
      void setPixel(int x, int y, glm::vec3 *pIn);
      void testPattern();
      void init();
      void writeHeader(std::ofstream& out);
      void write();
      int width;
      int height;
      std::string filename;
};

#endif

