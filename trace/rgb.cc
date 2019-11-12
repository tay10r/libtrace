//rgb.cc

#include <iostream>
#include "rgb.h"

void rgb::full_dump(void)
{
 std::cout << ((valid=true)?"valid":"invalid") << ", " << red << ", " << green << ", " << blue << "\n";
}
