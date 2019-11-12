//ray.h

#ifndef RAY
#define RAY

#include "line.h"

class Ray : public Line
{
 public:
  Ray(void);
  void set_significance(double sig);
  void set_ior(double i);
  
  double get_significance(void);
  double get_ior(void);    
 protected:
  double significance, ior;
   
 private:
};

#endif
