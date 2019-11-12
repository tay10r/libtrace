//scale.cc

#include <iostream>

#include "scale.h"

Scale::Scale(void)
{
 set_scale(Vector(1,1,1));
 set_objects(0);
}

Scale::Scale(Object *o)
{
 set_scale(Vector(1,1,1));
 set_objects(o);
}

Scale::Scale(Vector s)
{
 set_scale(s);
 set_objects(0);
}

Scale::Scale(Object *o, Vector s)
{
 set_scale(s);
 set_objects(o);
}

void Scale::set_scale(Vector s)
{
 scale=s;
}

void Scale::set_objects(Object *o)
{
 object.set_objects(o);
}

Object* Scale::get_objects(void)
{
 return object.get_objects();
}

Vector Scale::get_scale(void)
{
 return scale;
}

Vector Scale::_intersection(Line line) const
{
 line.set_start(line.get_start()/scale);
 line.set_direction(line.get_direction()/scale);
 
 Vector retval=object.intersection(line);
 if (retval.valid)
  retval=retval*scale;
 
 return retval;
}

Vector Scale::normal(void) const
{
 return (object.normal()*scale);
}

bool Scale::inside(void) const
{
 return object.inside();
}
