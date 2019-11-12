//scale.h

#ifndef SCALE
#define SCALE

#include "merge.h"

class Scale : public Object
{
 public:
  Scale(void);
  Scale(Object *o);
  Scale(Vector s);
  Scale(Object *o, Vector s);
  
  void set_objects(Object *o);
  void set_scale(Vector s);
  
  Object* get_objects(void);
  Vector get_scale(void);
  
  virtual bool inside(void) const;
 protected:
  virtual Vector _intersection(Line line) const;
  virtual Vector normal(void) const;

  Vector scale;
  Merge object;
 private:
};

#endif
