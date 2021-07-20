/* https://gist.github.com/pfigue/9ce8a2c0b14a2542acd7 
  int clock_gettime(clockid_t unused, struct timespec *tp)
  {
      (void) unused;
      uint64_t m = micros64();
      tp->tv_sec = m / 1000000;
      tp->tv_nsec = (m % 1000000) * 1000;
      return 0;
  }
*/
#include <stdio.h> 
#include <time.h> 
#include "sys_tick.h"

#define SYS_TICK_CONSOLE_DEBUG(f_, ...)          //fprintf(stdout, (f_), ##__VA_ARGS__)

uint64_t millis(void)
{
  struct timespec tp;
  clockid_t clk_id;
  uint64_t millis_cnt;

  clk_id = CLOCK_MONOTONIC;

  clock_gettime(clk_id, &tp);
  // tv_sec is long int and never negative
  millis_cnt = tp.tv_sec * 1000 + tp.tv_nsec / 1000000;
  SYS_TICK_CONSOLE_DEBUG("\ntp.tv_sec: %ld", tp.tv_sec);
  SYS_TICK_CONSOLE_DEBUG("\ntp.tv_nsec: %ld", tp.tv_nsec); 
  SYS_TICK_CONSOLE_DEBUG("\nmillis_cnt: %lu\n", millis_cnt); 

  return millis_cnt;
}
