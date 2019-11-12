//box.cc

#include "box.h"

Box::Box(void)
{
 left.set_child(&right);
 right.set_child(&top);
 top.set_child(&bottom);
 bottom.set_child(&front);
 
 box.set_objects(&back, &left);
 
 left.set_normal(Vector(1,0,0));
 right.set_normal(Vector(-1,0,0));
 top.set_normal(Vector(0,-1,0));
 bottom.set_normal(Vector(0,1,0));
 front.set_normal(Vector(0,0,1));
 back.set_normal(Vector(0,0,1));
 
 set_corners(Vector(0,0,0), Vector(1,1,1));
}

Vector Box::_intersection(Line line) const
{
 return box._intersection(line);
}

Vector Box::normal(void) const
{
 return box.normal();
}

bool Box::inside(void) const
{
 return box.inside();
}

void Box::set_corners(Vector a, Vector b)
{
 if (a.x>b.x)
 {
  double temp=a.x;
  a.x=b.x; b.x=temp;
 }
 
 if (a.y>b.y)
 {
  double temp=a.y;
  a.y=b.y; b.y=temp;
 }

 if (a.z>b.z)
 {
  double temp=a.z;
  a.z=b.z; b.z=temp;
 }

 left.set_offset(a.x);
 right.set_offset(-b.x);
 top.set_offset(-b.y);
 bottom.set_offset(a.y);
 front.set_offset(a.z);
 back.set_offset(b.z);
}

Vector Box::get_corner_a(void)
{
 return Vector(
  left.get_offset(),
  bottom.get_offset(),
  front.get_offset()
 );
}

Vector Box::get_corner_b(void)
{
 return Vector(
  -top.get_offset(),
  -top.get_offset(),
  back.get_offset()
 );
}
