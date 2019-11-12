//wood.cc
#include "wood.h"
#include "tplain.h"

Wood::Wood(void)
{
 min=max=0;
 
 noise=new Noise;
 (*noise).set_persistence(0.5);
 TPlain *tp0=new TPlain, *tp1=new TPlain;
  (*tp0).surface.diffuse=0;
  (*tp1).surface.diffuse=1.0;
 (*noise).min=tp0;
 (*noise).max=tp1;
}

Wood::~Wood(void)
{
 delete (*noise).min;
 delete (*noise).max;
 delete noise;
}

Surface Wood::_get_surface(Vector pos) const
{
 double g=(*noise).get_surface_(pos).diffuse;
 
 g=(g*5)+sqrt((pos.x*pos.x)+(pos.y*pos.y)+(pos.z*0.01*pos.z))*10;
 g=(g-(int)(g))/2;
 
 g+=(*noise).get_surface_(pos*Vector(100, 100, 20)).diffuse;

 if (g>1.0) g=1.0; 
 
 return (*min).get_surface_(pos)*(1.0-g) + (*max).get_surface_(pos)*g;
}

