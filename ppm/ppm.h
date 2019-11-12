#ifndef DOOPPM
#define DOOPPM

#include <iostream>

typedef unsigned short int ushortint;

struct Dimensions
{
 ushortint width, height;
};

struct Pixel
{
 unsigned char red, green, blue;
};

class PPM
{
 public:
  PPM(void);
  ~PPM(void);
  unsigned char *get_image(void);
  void set_image(unsigned char *new_image);
  void load_from_file(const char *filename);
  void load_from_stream(std::istream& in);
  void save_to_file(const char *filename);
  void save_to_stream(std::ostream& out);
  void set_width(ushortint new_width);
  void set_height(ushortint new_height);
  void set_dimensions(ushortint new_width, ushortint new_height);
  ushortint get_width(void);
  ushortint get_height(void);
  Dimensions get_dimensions(void);
  void allocate(void);
  void deallocate(void);
  Pixel get_pixel(ushortint x, ushortint y);
  void set_pixel(ushortint x, ushortint y, unsigned char red, unsigned char green, unsigned char blue);
  void set_pixel(ushortint x, ushortint y, Pixel);
 
 private:
  unsigned char *image;
  ushortint width, height;
  //my_image - if we allocated the memory
  //allocated - if the memory has been allocated at all by anyone yet
  bool my_image, allocated;
};

#endif
