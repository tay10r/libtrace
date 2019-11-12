//torus.h

#ifndef TORUS
#define TORUS

#include "object.h"

class Torus : public Object
{
 public:
  Torus(void);
  Torus(Vector center, double major, double minor);
  
  virtual Vector _intersection(Line line) const;
  virtual Vector normal(void) const;
  virtual bool inside(void) const;
  
  void set_major(double major);
  void set_minor(double minor);
  void set_center(Vector center);
  void set_major_and_minor(double major, double minor);
  
 protected:
  double r1, r2;
  Vector c, *norm;
  bool *ins;
 private:
};

#endif
