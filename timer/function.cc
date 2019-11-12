#include "timer.h"

unsigned long long Timer::ticks(void)
{
 unsigned long long time;
 asm("rdtsc" : "=A" (time));
 return time;
}
