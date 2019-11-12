//rotate.h

#ifndef ROTATE
#define ROTATE

#include "merge.h"

class Rotate : public Object
{
 public:
  Rotate(void);
  Rotate(Object *o);
  Rotate(Vector ax, double a);
  Rotate(Object *o, Vector ax, double a);
 
  void set_object(Object *o);
  void set_angle(double a);
  void set_axis(Vector ax);
  void set_axis_and_angle(Vector ax, double a);
  
  Object* get_object(void);
  Vector get_axis(void);
  double get_angle(void);
    
  virtual bool inside(void) const;
 protected:
  virtual Vector _intersection(Line line) const;
  virtual Vector normal(void) const;

  double angle;
  Vector axis;
  Merge object;
 private:
};

#endif
