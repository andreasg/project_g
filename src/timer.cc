
#include "timer.h"

void timer::on_timer() {}

Uint32 timer::timer_proc(Uint32 interval, void *param) {
  ((timer*)param)->on_timer();
  return interval;
}


