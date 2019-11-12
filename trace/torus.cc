//torus.cc

#include "torus.h"

Torus::Torus(void)
{
 NOT_WRITTEN_YET

 set_major_and_minor(0, 0);
 set_center(Vector(0,0,0));

 norm=new Vector;
 (*norm)=Vector(0,0,0);
 ins=new bool;
 (*ins)=false;
}

Torus::Torus(Vector c, double major, double minor)
{
 set_major_and_minor(major, minor);
 set_center(c);

 norm=new Vector;
 (*norm)=Vector(0,0,0);
 ins=new bool;
 (*ins)=false;
}

void Torus::set_major_and_minor(double major, double minor)
{
 set_major(major);
 set_minor(minor);
}

void Torus::set_center(Vector center)
{
 c=center;
}

void Torus::set_major(double major)
{
 r1=major;
}

void Torus::set_minor(double minor)
{
 r2=minor;
}

Vector Torus::_intersection(Line line) const
{
 //Translate scene so that the torus is at the origin
 line.set_start(line.get_start()-center);
 
 
 
 //Un-Translate scene so that the answer is actually correct
 retval=retval+center;
 return retval;
}
