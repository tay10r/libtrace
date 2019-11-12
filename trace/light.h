//light.h

#ifndef LIGHT
#define LIGHT

#include "list.h"
#include "vector.h"
#include "rgb.h"

class Light : public List
{
 public:
  Light(void);
  Light(Vector pos, rgb col);
  
  void set_position(Vector pos);
  void set_color(rgb col);
  
  Vector get_position(void);
  rgb get_color(void);
 
 protected:
  Vector position;
  rgb color;
 private:
};

#endif
