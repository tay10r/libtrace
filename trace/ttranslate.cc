//ttranslate.cc

#include "ttranslate.h"

TTranslate::TTranslate(void)
{
 texture=0;
}

Surface TTranslate::_get_surface(Vector pos) const
{
 return (*texture).get_surface_((pos-translate));
}
