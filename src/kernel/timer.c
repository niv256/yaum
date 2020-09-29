#include "timer.h"
#include "isr.h"
#include "screen.h"

uint32_t time;

static void watch(void) {
#if 0
  if (time % 1000 == 0) {
    terminal_writestring("Tick: ");
    terminal_writeint(time, 10);
    terminal_putchar('\n');
  }
#endif
  time += 55;
}

void timer_init(void) {
  setup_isr_callback(IRQ0, &watch);
}
