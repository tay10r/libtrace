//tchecked.h

#ifndef TCHECKED
#define TCHECKED

#include "texture.h"

class TChecked : public Texture
{
 public:
  Texture *texture_a, *texture_b;
 protected:
  virtual Surface _get_surface(Vector pos) const;
 private:
};

#endif
