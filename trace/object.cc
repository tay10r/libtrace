//object.cc

#include <iostream>

#include "object.h"
#include "tplain.h"

Object::Object(void)
{
 lip=new Vector;
 texture=0;
}

Object::~Object(void)
{
 delete lip;
}

Vector Object::intersection(Line line) const
{
 (*lip)=_intersection(line);
 return (*lip);
}

Vector Object::_intersection(Line line) const
{
 (void)line;
 SHOULD_NOT_GET_HERE
 exit(255);
 return Z;
}

Surface Object::get_surface(void)
{
 Surface retval;
 if (texture!=0)
 {
  retval=(*texture).get_surface((*lip));
 } else
 {
  TPlain temp;
  retval=temp.get_surface((*lip));
 }
 
 Vector norm=normal();
 norm.normalize();
 retval.normal=retval.normal+norm;
 return retval;
}

Vector Object::normal(void) const
{
 SHOULD_NOT_GET_HERE
 exit(255);
 return Z;
}

bool Object::inside(void) const
{
 SHOULD_NOT_GET_HERE
 exit(255);
 return false;
}
