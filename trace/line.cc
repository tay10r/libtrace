//line.cc

#include <iostream>
#include "line.h"

Line::Line(void)
{
 start=Vector(0,0,0);
 direction=Vector(0,0,1);
}

Line::Line(Vector s, Vector d)
{
 set_start_and_direction(s,d);
}

void Line::set_start(Vector s)
{
 start=s;
}

void Line::set_direction(Vector d)
{
 direction=d;
}

void Line::set_start_and_direction(Vector s, Vector d)
{
 set_start(s);
 set_direction(d);
}

Vector Line::get_start(void)
{
 return start;
}

Vector Line::get_direction(void)
{
 return direction;
}
