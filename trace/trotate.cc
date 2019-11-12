//trotate.cc

#include "trotate.h"

TRotate::TRotate(void)
{
 axis=X;
 angle=0;
 texture=0;
}

Surface TRotate::_get_surface(Vector pos) const
{
 return (*texture).get_surface_(rotate(pos, axis, -angle));
}
