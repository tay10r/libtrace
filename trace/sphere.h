//sphere.h

#ifndef SPHERE
#define SPHERE

#include "object.h"

class Sphere : public Object
{
 public:
  Sphere(void);
  Sphere(Vector c, double r);
  virtual ~Sphere(void);
  
  void set_center(Vector c);
  Vector get_center(void);
  void set_radius(double r);
  double get_radius(void);
  virtual bool inside(void) const;

 protected:
  virtual Vector normal(void) const;
  virtual Vector _intersection(Line line) const;

 private:
  Vector center;
  double radius;
  Vector *norm;
  bool *ins;
};

#endif
