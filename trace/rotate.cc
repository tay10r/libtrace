//rotate.cc

#include "rotate.h"

Rotate::Rotate(void)
{
 set_axis_and_angle(X, 0);
 set_object(0);
}

Rotate::Rotate(Object *o)
{
 set_axis_and_angle(X, 0);
 set_object(o);
}

Rotate::Rotate(Vector ax, double a)
{
 set_axis_and_angle(ax, a);
 set_object(0);
}

Rotate::Rotate(Object *o, Vector ax, double a)
{
 set_axis_and_angle(ax, a);
 set_object(o);
}

void Rotate::set_object(Object *o)
{
 object.set_objects(o);
}

void Rotate::set_axis_and_angle(Vector ax, double a)
{
 set_axis(ax);
 set_angle(a);
}

void Rotate::set_axis(Vector ax)
{
 axis=ax;
 axis.normalize();
}

void Rotate::set_angle(double a)
{
 angle=a;
}

Object* Rotate::get_object(void)
{
 return object.get_objects();
}

Vector Rotate::get_axis(void)
{
 return axis;
}

double Rotate::get_angle(void)
{
 return angle;
}

Vector Rotate::_intersection(Line line) const
{
 line.set_start( rotate(line.get_start(), axis, -angle) );
 line.set_direction( rotate(line.get_direction(), axis, -angle) );
 
 Vector retval=object.intersection(line);
 if (retval.valid)
  retval=rotate(retval, axis, angle);
 
 return retval;
}

Vector Rotate::normal(void) const
{
 return rotate(object.normal(), axis, angle);
}

bool Rotate::inside(void) const
{
 return object.inside();
}
