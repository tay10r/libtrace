//wood.h

#ifndef WOOD
#define WOOD

#include "noise.h"

class Wood : public Texture
{
 public:
  Wood(void);
  virtual ~Wood(void);
  
  Texture *min, *max;

 protected:
  Noise *noise;
  virtual Surface _get_surface(Vector pos) const;

 private:
};

#endif
