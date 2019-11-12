//cylinder.h

#ifndef CYLINDER
#define CYLINDER

#include "object.h"

class Cylinder : public Object
{
 public:
  Cylinder(void);
  virtual ~Cylinder(void);
 
  virtual bool inside(void) const;
  void set_length(double l);
  void set_radius_a(double r1);
  void set_radius_b(double r2);

 protected:
  virtual Vector _intersection(Line line) const;
  virtual Vector normal(void) const;

 private:
  double a, i, j;
  
  //a is the length of the cylinder
  //i is the radius of the culinder at one end
  //j is the radius of the cylinder at the other end
  bool *ins, *hit_side;
};

#endif
