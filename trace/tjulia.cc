//tjulia.cc

#include "tjulia.h"

TJulia::TJulia(void)
{
 max_iter=256;
 attract=-1;
 escape=100;
 max=min=0;
}

std::complex<double> TJulia::function(std::complex<double> x) const
{
 std::complex<double> b(1.0, 0.16);
 return (b*sin(x));
 //SHOULD_NOT_GET_HERE
 return x;
}

Surface TJulia::_get_surface(Vector pos) const
{
 std::complex<double> x(pos.x,pos.y);
 int iter=0;
 double mag;

 // TODO: implement "plug-in" system for julia functions 
 
 do
 {
  x=function(x);
  mag=sqrt( x.real()*x.real() + x.imag()*x.imag() );
  iter++;
 } while ( (mag>attract)&&(mag<escape)&&(iter<max_iter) );
 
 mag=static_cast<double>(iter)/static_cast<double>(max_iter);
 return (*min).get_surface_(pos)*(1.0-mag) + (*max).get_surface_(pos)*mag;
}
