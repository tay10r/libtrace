//light.cc

#include "light.h"

Light::Light(void)
{
 set_position(Vector(0,0,0));
 set_color(BLACK);
}

Light::Light(Vector pos, rgb col)
{
 set_position(pos);
 set_color(col);
}

void Light::set_position(Vector pos)
{
 position=pos;
}

void Light::set_color(rgb col)
{
 color=col;
}

Vector Light::get_position(void)
{
 return position;
}

rgb Light::get_color(void)
{
 return color;
}
