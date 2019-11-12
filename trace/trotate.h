//trotate.h

#ifndef TROTATE
#define TROTATE

#include "texture.h"

class TRotate : public Texture
{
 public:
  TRotate(void);
 
  Texture *texture;
  Vector axis;
  double angle;
 protected:
  virtual Surface _get_surface(Vector pos) const;
 private:
};

#endif
