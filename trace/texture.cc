//texture.cc

#include "texture.h"

Texture::Texture(void)
{
 master=slave=0;
}

Surface Texture::get_surface(Vector pos)
{
 Surface retval=get_surface_(pos);

 if (!retval.normal.valid) retval.normal=Vector(0,0,0);
 if (!retval.color.valid) retval.color=BLACK;
 if (retval.diffuse<0) retval.diffuse=0;
 if (retval.specular<0) retval.specular=0;
 if (retval.hardness<0) retval.hardness=0;
 if (retval.transparency<0) retval.transparency=0;
 if (retval.reflect<0) retval.reflect=0;
 if (retval.refract<0) retval.refract=0;
 if (retval.ior<0) retval.ior=1;

 return retval; 
}

Surface Texture::get_surface_(Vector pos)
{
 Surface retval, me=_get_surface(pos);

 if (slave!=0)
 {
  retval=(*slave).get_surface_(pos);
   
  if (me.normal.valid) retval.normal=me.normal;
  if (me.color.valid) retval.color=me.color;
  if (!(me.diffuse<0)) retval.diffuse=me.diffuse;
  if (!(me.specular<0)) retval.specular=me.specular;
  if (!(me.hardness<0)) retval.hardness=me.hardness;
  if (!(me.transparency<0)) retval.transparency=me.transparency;
  if (!(me.reflect<0)) retval.reflect=me.reflect;
  if (!(me.refract<0)) retval.refract=me.refract;
  if (!(me.ior<0)) retval.ior=me.ior;

 } else
 {
  retval=me;
 }
  
 if (master!=0)
 {
  Surface mast=(*master).get_surface_(pos);
 
  if (mast.normal.valid) retval.normal=mast.normal;
  if (mast.color.valid) retval.color=mast.color;
  if (!(mast.diffuse<0)) retval.diffuse=mast.diffuse;
  if (!(mast.specular<0)) retval.specular=mast.specular;
  if (!(mast.hardness<0)) retval.hardness=mast.hardness;
  if (!(mast.transparency<0)) retval.transparency=mast.transparency;
  if (!(mast.reflect<0)) retval.reflect=mast.reflect;
  if (!(mast.refract<0)) retval.refract=mast.refract;
  if (!(mast.ior<0)) retval.ior=mast.ior;
 }
 
 return retval;
}

Surface Texture::_get_surface(Vector pos) const
{
 SHOULD_NOT_GET_HERE
 (void)pos;
 Surface retval;
 return retval;
}
