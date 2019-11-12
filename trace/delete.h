//delete.h

#ifndef DELETE
#define DELETE

#include "merge.h"

class Delete : public Object
{
 public:
  Delete(void);
  Delete(Object* a, Object* b);
  ~Delete(void);
  
  virtual Vector _intersection(Line line) const;
  virtual Vector normal(void) const;
  virtual bool inside(void) const;
  
  void set_objects(Object* a, Object* b);
 
 protected:
  Merge parta, partb;
  bool *ins;
  Vector *norm;
 private:
};

#endif
