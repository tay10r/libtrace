//noise.h

#ifndef NOISE
#define NOISE

#include "texture.h"

class Noise : public Texture
{
 public:
  Noise(void);
  virtual ~Noise(void);
  
  void set_persistence(double persistence);

  Texture *min, *max;
  
 protected:
  int amps;
  double *amp;
   
  double interpolate(double a, double b, double x) const;
  double get_rnd(int x, int y, int z, int layer) const;
  
  virtual Surface _get_surface(Vector pos) const;
 private:
};

#endif
