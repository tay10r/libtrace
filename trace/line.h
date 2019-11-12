//line.h

#ifndef LINE
#define LINE

#include "vector.h"

class Line
{
 public:
  Line(void);
  Line(Vector s, Vector d);
  void set_start(Vector s);
  void set_direction(Vector d);
  void set_start_and_direction(Vector s, Vector d);
  Vector get_start(void);
  Vector get_direction(void);
 protected:
  Vector start, direction;
 private:
};

#endif
