//noise.cc

#include <stdlib.h>
#include <math.h>

#include "noise.h"

Noise::Noise(void)
{
 amps=1;
 amp=new double;
 (*amp)=0;
 min=max=0;
 set_persistence(0.5);
}

Noise::~Noise(void)
{
 delete [] amp;
}

void Noise::set_persistence(double persistence)
{
 delete [] amp;

 if ( !(persistence<1) )
  persistence=0;
  
 double amp_t=1, scale=1;
 amps=0;
  
 //Quick skim through to check the maximum depth..  (I know logs would work but this is quicker)
 while ( amp_t>(scale/256.0) )
 {
  amp_t*=persistence;
  scale+=amp_t;
  
  amps++;
 }
 
 amp = new double[amps];
 amp_t=1/scale;

 for (int c=0;c<amps;c++)
 {
  (*(amp+c))=amp_t;
  amp_t*=persistence;
 }
}

Surface Noise::_get_surface(Vector pos) const
{
 int freq=1;
 double total=0;
 
 for (int level=0;level<amps;level++)
 {
  double
   x=pos.x*freq,
   y=pos.y*freq,
   z=pos.z*freq;
  int
   xi=static_cast<int>(x)-((x<0)?(1):(0)),
   yi=static_cast<int>(y)-((y<0)?(1):(0)),
   zi=static_cast<int>(z)-((z<0)?(1):(0));
  double
   xf=x-xi,
   yf=y-yi,
   zf=z-zi,
   c0=get_rnd(xi, yi, zi, level),
   c1=get_rnd(xi, yi, zi+1, level),
   c2=get_rnd(xi, yi+1, zi, level),
   c3=get_rnd(xi, yi+1, zi+1, level),
   c4=get_rnd(xi+1, yi, zi, level),
   c5=get_rnd(xi+1, yi, zi+1, level),
   c6=get_rnd(xi+1, yi+1, zi, level),
   c7=get_rnd(xi+1, yi+1, zi+1, level),
   d0=interpolate(c0, c1, zf),
   d1=interpolate(c2, c3, zf),
   d2=interpolate(c4, c5, zf),
   d3=interpolate(c6, c7, zf),
   e0=interpolate(d0, d1, yf),
   e1=interpolate(d2, d3, yf),
   f=interpolate(e0, e1, xf)*(*(amp+level));
  
  total+=f;
  
  freq*=2;
 }
 
 Surface retval;
 retval=(*min).get_surface_(pos)*(1.0-total) + (*max).get_surface_(pos)*total;

 return retval;
}


double Noise::get_rnd(int x, int y, int z, int layer) const
{
 // #warning TODO: make this function more random

 /*
  This function is supposed to return a random number in the range 0.0 to 1.0
  dependant on the input variables.
  
  The function should return the same number twice if the same input values are
  given each time.
  
  At the moment noticable patterns are produced in the "random" numbers
  generated.
 */

 x=(x*143631)%35417;
 x=(x*648861)%89587;

 y=(y*984597)%49873;
 y=(y*894389)%48949;

 z=(z*121375)%46187;
 z=(z*456883)%46479;

 layer=(layer*464347)%68445;
 layer=(layer*987645)%16786;

 int r=(int)+(x*846123 + y*844619 + z*687137 + layer*984685);
 
 r=(r*164631)%98415;
 r=(r*676431)%78949;

 double rnd=static_cast<double>(abs(r)%65189)/65189.0;
 
 return rnd;
}

double Noise::interpolate(double a, double b, double x) const
{
 return ( (a-b)*(cos(x*M_PI)+1)*0.5 + b );
}
