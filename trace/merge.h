//merge.h

#ifndef MERGE
#define MERGE

#include "object.h"

class Merge : public Object
{
 public:
  Merge(void);
  Merge(Object* obj);
  ~Merge(void);
  virtual Vector _intersection(Line line) const;
  virtual Vector normal(void) const;
  virtual bool inside(void) const;
  void set_objects(Object* obj);
  Object* get_objects(void) const;
  
 protected:
  Object *objects;
  Vector *norm;
  bool *ins;
 private:
};

#endif
