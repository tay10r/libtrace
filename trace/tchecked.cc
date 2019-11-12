//tchecked.cc

#include "tchecked.h"

Surface TChecked::_get_surface(Vector pos) const
{
 return (
  ((static_cast<int>( ((pos.x<0)?(-pos.x+1):pos.x) )%2)^
  (static_cast<int>( ((pos.y<0)?(-pos.y+1):pos.y) )%2)^
  (static_cast<int>( ((pos.z<0)?(-pos.z+1):pos.z) )%2))
  ?((*texture_a).get_surface_(pos)):((*texture_b).get_surface_(pos)));
}
