#include <arch/i386/isr.h>
#include <etc/timer.h>
#include <io/screen.h>

#define TICK 55

size_t ticks;
size_t interval;
bool verbose;

static void watch(registers_t regs) {
  if (verbose && ticks % interval < TICK) {
    terminal_writestring("system time (in seconds): ");
    terminal_writedec(MS_TO_SECOND(ticks));
    terminal_newline();
  }
  ticks += TICK;
}

void timer_init(bool verbose, size_t interval) {
  setup_isr_callback(IRQ0, &watch);
  timer_set_verbose(verbose);
  timer_set_print_interval_ms(interval);
}

void timer_set_verbose(bool _verbose) {
  verbose = _verbose;
}

void timer_set_print_interval_ms(size_t _interval) {
  interval = _interval;
}

void timer_set_print_interval_seconds(size_t _interval) {
  interval = SECOND_TO_MS(_interval);
}
