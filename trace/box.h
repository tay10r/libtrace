//box.h

#ifndef BOX
#define BOX

#include "delete.h"
#include "plane.h"

class Box : public Object
{
 public:
  Box(void);
  
  void set_corners(Vector a, Vector b);
  Vector get_corner_a(void);
  Vector get_corner_b(void);
  
  virtual bool inside(void) const;
  
 protected:
  virtual Vector normal(void) const;
  virtual Vector _intersection(Line line) const; 
 
  Plane left,right,top,bottom,front,back;
  Delete box;
 private:
};

#endif
