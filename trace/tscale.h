//tscale.h

#ifndef TSCALE
#define TSCALE

#include "texture.h"

class TScale : public Texture
{
 public:
  TScale(void);
  
  Texture *texture;
  Vector scale;
 protected:
  virtual Surface _get_surface(Vector pos) const;
 private:
};

#endif
