#include "timer.h"
#include "isr.h"
#include "screen.h"

#define TICK 55

uint32_t ticks;
uint32_t interval;
uint8_t verbose;

static void watch(registers_t regs) {
  if (verbose && ticks % interval < TICK) {
    terminal_writestring("system time (in seconds): ");
    terminal_writedec(MS_TO_SECOND(ticks));
    terminal_newline();
  }
  ticks += TICK;
}

void timer_init(uint8_t verbose, uint32_t interval) {
  setup_isr_callback(IRQ0, &watch);
  timer_set_verbose(verbose);
  timer_set_print_interval_ms(interval);
}

void timer_set_verbose(uint8_t _verbose) {
  verbose = _verbose;
}

void timer_set_print_interval_ms(uint32_t _interval) {
  interval = _interval;
}

void timer_set_print_interval_seconds(uint32_t _interval) {
  interval = SECOND_TO_MS(_interval);
}
