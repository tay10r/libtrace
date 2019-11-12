//plane.cc

#include "plane.h"
#include <iostream>

Plane::Plane(void)
{
 set_normal(Vector(0,1,0));
 set_offset(0);
 ins=new bool;
 (*ins)=false;
}

Plane::Plane(Vector nor, double off)
{
 set_normal(nor);
 set_offset(off);
 ins=new bool;
 (*ins)=false;
}

Plane::~Plane(void)
{
 delete ins;
}

void Plane::set_normal(Vector nor)
{
 norm=nor;
}

void Plane::set_offset(double off)
{
 offset=off;
}

Vector Plane::get_normal(void)
{
 return norm;
}

double Plane::get_offset(void)
{
 return offset;
}

//Algorithm by bineng
//coded by pauldoo
Vector Plane::_intersection(Line l) const
{
 //These #defines are to make the variables match those written down  :)
#define r l.get_start()
#define v l.get_direction()
#define n norm
#define d offset
 
 Vector retval;

 double nr=dot(n,r);

 if ((nr-d)>0)
 {
  (*ins)=false;
 } else
 {
  (*ins)=true;
 }
 
 double nv=dot(n, v);
 if (nv!=0)
 {

  double t=(d-nr)/nv;
  if (t>0)
  {
   retval=r+t*v;
  }else
  {
   retval.valid=false;
  }
 }else
 {
  retval.valid=false;
 }

#undef r
#undef v
#undef n
#undef d

 return retval;
}

Vector Plane::normal(void) const
{
 Vector retval=norm;
 if ( (*ins) )
 {
  retval=retval*(-1.0);
 }
 
 return retval;
}

bool Plane::inside(void) const
{
 return (*ins);
}
