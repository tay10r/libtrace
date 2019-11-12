#include <stdlib.h>

#include "ppm.h"

PPM::PPM(void)
{
 if (sizeof(ushortint)!=2)
 {
  std::cout << "Please redefine \"ushortint\" to be 2 bytes long\n";
  exit(0);
 }
 my_image=false;
 set_dimensions(0, 0);
 deallocate();
}

PPM::~PPM(void)
{
 deallocate();
}

unsigned char *PPM::get_image(void)
{
 return image;
}

void PPM::set_image(unsigned char *new_image)
{
 if (my_image)
  delete [] image;
 image=new_image;
 my_image=false;
 allocated=true;
}

void PPM::set_height(ushortint new_height)
{
 deallocate();
 height=new_height;
}

void PPM::set_width(ushortint new_width)
{
 deallocate();
 width=new_width;
}

void PPM::set_dimensions(ushortint new_width, ushortint new_height)
{
 set_width(new_width);
 set_height(new_height);
}

void PPM::allocate(void)
{
 set_image(new unsigned char[width*height*3]);
 my_image=true;
}

void PPM::deallocate(void)
{
 set_image(0);
 allocated=false;
}

ushortint PPM::get_width(void)
{
 return width;
}

ushortint PPM::get_height(void)
{
 return height;
}

Dimensions PPM::get_dimensions(void)
{
 Dimensions a;
 a.width=get_width();
 a.height=get_height();
 
 return a;
}

Pixel PPM::get_pixel(ushortint x, ushortint y)
{
 Pixel a;
 unsigned char *spot=get_image()+((y*width)+x)*3;
 a.red=(*spot);
 a.green=(*(spot+1));
 a.blue=(*(spot+2));
 
 return a;
}

void PPM::set_pixel(ushortint x, ushortint y, Pixel a)
{
 unsigned char *spot=get_image()+((y*width)+x)*3;
 (*spot)=a.red;
 (*(spot+1))=a.green;
 (*(spot+2))=a.blue;
}

void PPM::set_pixel(ushortint x, ushortint y, unsigned char red, unsigned char green, unsigned char blue)
{
 Pixel a;
 a.red=red;
 a.green=green;
 a.blue=blue;
 set_pixel(x, y, a);
}
