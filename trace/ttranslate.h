//ttranslate.h

#ifndef TTRANSLATE
#define TTRANSLATE

#include "texture.h"

class TTranslate : public Texture
{
 public:
  TTranslate(void);
  Texture *texture;
  Vector translate;
 protected:
  virtual Surface _get_surface(Vector pos) const;
 private: 
};

#endif
