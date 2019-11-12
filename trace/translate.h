//translate.h

#ifndef TRANSLATE
#define TRANSLATE

#include "merge.h"

class Translate : public Object
{
 public:
  Translate(void);
  Translate(Object *o);
  Translate(Vector t);
  Translate(Object *o, Vector t);
  
  void set_object(Object *o);
  void set_translate(Vector t);
  void set_object_and_translate(Object *o, Vector t);
  
  Object* get_object(void);
  Vector get_translate(void);
  
  virtual bool inside(void) const;
 protected:
  virtual Vector _intersection(Line line) const;
  virtual Vector normal(void) const;

  Vector trans;
  Merge object;
 private:
};

#endif
