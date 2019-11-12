//texture.h

#ifndef TEXTURE
#define TEXTURE

#include "surface.h"

class Texture
{
 public:
  Texture(void);
  virtual ~Texture() { }
 
  Surface get_surface(Vector pos);  //Finds the overall texture ready for scene2.cc to use
  Surface get_surface_(Vector pos); //Finds the overall texture ready for more textures to be applied
  Texture *master,*slave;

 protected:
  virtual Surface _get_surface(Vector pos) const; //Finds this texture only

 private:
};

#endif
