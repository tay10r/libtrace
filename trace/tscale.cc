//tscale.cc

#include "tscale.h"

TScale::TScale(void)
{
 texture=0;
 scale=Vector(1,1,1);
}

Surface TScale::_get_surface(Vector pos) const
{
 return (*texture).get_surface_(pos/scale);
}
