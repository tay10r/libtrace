//rgb.h

#ifndef RGB
#define RGB

#include "defines.h"

#define BLACK (rgb(0, 0, 0))
#define WHITE (rgb(1, 1, 1))
#define GREY (rgb(0.5, 0.5, 0.5))

#define RED (rgb(1, 0, 0))
#define GREEN (rgb(0, 1, 0))
#define BLUE (rgb(0, 0, 1))

#define YELLOW (rgb(1, 1, 0))
#define CYAN (rgb(0, 1, 1))
#define MAGENTA (rgb(1, 0, 1))

class rgb
{
 public:
  rgb(void);
  rgb(double r, double g, double b);
  rgb(bool v);

  void clip(void);
  double red, green, blue;
  bool valid;
  
  void full_dump(void);
 protected:
 private:
};

rgb operator+(rgb a, rgb b);
rgb operator-(rgb a, rgb b);
rgb operator*(rgb a, rgb b);
rgb operator*(rgb a, double b);
 rgb operator*(double b, rgb a);
rgb operator/(rgb a, double b);


inline rgb::rgb(void)
{
 red=green=blue=0;
 valid=true;
}

inline rgb::rgb(double r, double g, double b)
{
 red=r;
 green=g;
 blue=b;
 valid=true;
}

inline rgb::rgb(bool v)
{
 red=green=blue=0;
 valid=v;
}

inline void rgb::clip(void)
{
 if (red<0)
  red=0;
 else
  if (red>1)
   red=1;

 if (green<0)
  green=0;
 else
  if (green>1)
   green=1;

 if (blue<0)
  blue=0;
 else
  if (blue>1)
   blue=1;
}

inline rgb operator+(rgb a, rgb b)
{
 a.red+=b.red;
 a.green+=b.green;
 a.blue+=b.blue;
 return a;
}

inline rgb operator-(rgb a, rgb b)
{
 a.red-=b.red;
 a.green-=b.green;
 a.blue-=b.blue;
 return a;
}

inline rgb operator*(rgb a, rgb b)
{
 a.red*=b.red;
 a.green*=b.green;
 a.blue*=b.blue;
 return a;
}

inline rgb operator*(rgb a, double b)
{
 a.red*=b;
 a.green*=b;
 a.blue*=b;
 return a;
}

 inline rgb operator*(double b, rgb a)
 {
  return a*b;
 }

inline rgb operator/(rgb a, double b)
{
 a.red/=b;
 a.green/=b;
 a.blue/=b;
 return a;
}

#endif
