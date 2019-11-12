//translate.cc

#include "translate.h"

Translate::Translate(void)
{
 set_object_and_translate(0, Vector(0,0,0));
}

Translate::Translate(Object *o)
{
 set_object_and_translate(o, Vector(0,0,0));
}

Translate::Translate(Vector t)
{
 set_object_and_translate(0, t);
}

Translate::Translate(Object *o, Vector t)
{
 set_object_and_translate(o, t);
}

void Translate::set_object_and_translate(Object *o, Vector t)
{
 set_object(o);
 set_translate(t);
}

void Translate::set_object(Object *o)
{
 object.set_objects(o);
}

void Translate::set_translate(Vector t)
{
 trans=t;
}

Vector Translate::_intersection(Line line) const
{
 line.set_start(line.get_start()-trans);
 
 Vector retval=object.intersection(line);
 if (retval.valid)
  retval=retval+trans;
  
 return retval; 
}

Vector Translate::normal(void) const
{
 return object.normal();
}

bool Translate::inside(void) const
{
 return object.inside();
}
