//plane.h

#ifndef PLANE
#define PLANE

#include "object.h"

class Plane : public Object
{
 public:
  Plane(void);
  Plane(Vector nor, double off);
  virtual ~Plane(void);
  
  virtual bool inside(void) const;
  
  void set_normal(Vector nor);
  void set_offset(double off);
  Vector get_normal(void);
  double get_offset(void);
  
 protected:
  virtual Vector _intersection(Line line) const;
  virtual Vector normal(void) const;

  Vector norm;
  double offset;
  bool *ins;
 private:
};

#endif
