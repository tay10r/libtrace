//ray.cc

#include "ray.h"

Ray::Ray(void)
{
 set_significance(0);
 set_ior(1.0);
}

void Ray::set_significance(double sig)
{
 significance=sig;
}

void Ray::set_ior(double i)
{
 ior=i;
}

double Ray::get_significance(void)
{
 return significance;
}

double Ray::get_ior(void)
{
 return ior;
}
