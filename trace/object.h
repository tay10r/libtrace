//object.h

#ifndef OBJECT
#define OBJECT

#include "list.h"
#include "line.h"
#include "rgb.h"
#include "texture.h"

class Object : public List
{
 public:
  Object(void);
  virtual ~Object(void);
  
  Vector intersection(Line line) const;
  virtual bool inside(void) const;
  
  Surface get_surface(void);
  Texture *texture;
  
 protected:
  virtual Vector normal(void) const;
  virtual Vector _intersection(Line line) const;

  Vector *lip; //Last Intersection Point
 private:
};

#endif
