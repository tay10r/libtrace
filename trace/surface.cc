//surface.cc

#include "surface.h"

Surface::Surface(void)
{
 normal.valid=false;
 color.valid=false;
 diffuse=specular=hardness=transparency=reflect=refract=ior=-1;
}

//************
//* Addition *
//************

inline Vector add_vect(Vector a, Vector b)
{
 //Nice and simple logic really..  :)
 Vector retval=( (a.valid)?( (b.valid)?(a+b):(a) ):( (b.valid)?(b):(Vector(false)) ) );
 return retval;
}

inline rgb add_rgb(rgb a, rgb b)
{
 rgb retval=( (a.valid)?( (b.valid)?(a+b):((a)) ):( (b.valid)?(b):(rgb(false)) ) );
 return retval;
}

inline double add_dbl(double a, double b)
{
 double retval=( (!(a<0))?( (!(b<0))?(a+b):(a) ):( (!(b<0))?(b):(-1) ) );
 return retval;
}

//******************
//* Multiplication *
//******************

inline Vector mult_vect(Vector a, Vector b)
{
 //Nice and simple logic really..  :)
 Vector retval=( (a.valid&&b.valid)?(a*b):(Vector(false)) );
 return retval;
}

inline rgb mult_rgb(rgb a, rgb b)
{
 //Nice and simple logic really..  :)
 rgb retval=( (a.valid&&b.valid)?(a*b):(rgb(false)) );
 return retval;
}

inline double mult_dbl(double a, double b)
{
 //Nice and simple logic really..  :)
 double retval=( ((!(a<0))&&(!(b<0)))?(a*b):(-1) );
 return retval;
}

Surface operator+(Surface a, Surface b)
{
 Surface c;

 c.normal=add_vect(a.normal, b.normal);
 c.color=add_rgb(a.color, b.color);
 c.diffuse=add_dbl(a.diffuse, b.diffuse);
 c.specular=add_dbl(a.specular, b.specular);
 c.hardness=add_dbl(a.hardness, b.hardness);
 c.transparency=add_dbl(a.transparency, b.transparency);
 c.reflect=add_dbl(a.reflect, b.reflect);
 c.refract=add_dbl(a.refract, b.refract);
 c.ior=add_dbl(a.ior, b.ior);
 
 return c;
}

Surface operator*(Surface a, Surface b)
{
 Surface c;

 c.normal=mult_vect(a.normal, b.normal);
 c.color=mult_rgb(a.color, b.color);
 c.diffuse=mult_dbl(a.diffuse, b.diffuse);
 c.specular=mult_dbl(a.specular, b.specular);
 c.hardness=mult_dbl(a.hardness, b.hardness);
 c.transparency=mult_dbl(a.transparency, b.transparency);
 c.reflect=mult_dbl(a.reflect, b.reflect);
 c.refract=mult_dbl(a.refract, b.refract);
 c.ior=mult_dbl(a.ior, b.ior);
 
 return c;
}

Surface operator*(Surface a, double b)
{
 Surface c;

 c.normal=( (a.normal.valid&&(!(b<0)))?(a.normal*b):(Vector(false)) );
 c.color=( (a.color.valid&&(!(b<0)))?(a.color*b):(rgb(false)) );
 c.diffuse=mult_dbl(a.diffuse, b);
 c.specular=mult_dbl(a.specular, b);
 c.hardness=mult_dbl(a.hardness, b);
 c.transparency=mult_dbl(a.transparency, b);
 c.reflect=mult_dbl(a.reflect, b);
 c.refract=mult_dbl(a.refract, b);
 c.ior=mult_dbl(a.ior, b);
 
 return c;
}
