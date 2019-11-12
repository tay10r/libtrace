#ifndef TIMER_H
#define TIMER_H

class Timer
{
 public:
  Timer(void);
  void update(void);
  void reset(void);
  double read(void);
  double read_step(void);
  void skip(void);
  void set(double time);
  double accuracy(void);
  
 private:
  unsigned long long old, now, offset, ticks_per_second;
  unsigned long long ticks(void);
};

#endif
