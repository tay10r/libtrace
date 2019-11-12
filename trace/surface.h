//surface.h

#ifndef SURFACE
#define SURFACE

#include "vector.h"
#include "rgb.h"

class Surface
{
 public:
  Surface(void);
  
  Vector normal;
  rgb color;
  double diffuse, specular, hardness, transparency, reflect, refract, ior;
 protected:
 private:
};

Surface operator+(Surface a, Surface b);
Surface operator*(Surface a, Surface b);
 Surface operator*(Surface a, double b);

#endif
