//tplain.h

#ifndef TPLAIN
#define TPLAIN

#include "texture.h"

class TPlain : public Texture
{
 public:
  Surface surface;
  
 protected:
  virtual Surface _get_surface(Vector pos) const;
  
 private:
};

#endif
