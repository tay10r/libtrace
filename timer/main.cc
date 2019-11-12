#include "timer.h"
#include <time.h>

Timer::Timer(void)
{
 reset();
}

void Timer::reset(void)
{

 unsigned long long time1, time2;
 timespec req, rem;

 //Count the number of ticks in one second
 req.tv_sec=1;
 req.tv_nsec=0;
 time1=ticks();
 while (nanosleep(&req,&rem)==(-1))
  { req=rem; }
 time2=ticks();
 
 ticks_per_second=time2-time1;
 
 //Count the number of ticks required for the basic cycle of above
 req.tv_sec=0;
 req.tv_nsec=0;
 time1=ticks();
 while (nanosleep(&req,&rem)==(-1))
  { req=rem; }
 time2=ticks();
 
 //Subtract the empty cycle from the one second cycle
 ticks_per_second-=(time2-time1);


 //ticks_per_second=450000000; 
 //Actually reset the timer
 offset=old=now=ticks();
}

double Timer::accuracy(void)
{
 return (1/static_cast<double>(ticks_per_second));
}

double Timer::read(void)
{
 return ((now-offset)/static_cast<double>(ticks_per_second));
}

void Timer::skip(void)
{
 offset+=(now-old);
}

double Timer::read_step(void)
{
 return ((now-old)/static_cast<double>(ticks_per_second));
}

void Timer::set(double time)
{
 offset=static_cast<unsigned long long>(now-(time*ticks_per_second));
}

void Timer::update(void)
{
 old=now;
 now=ticks();
}
