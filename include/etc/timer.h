#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define TIMER_VERBOSE 1
#define TIMER_SILENT  0

#define SECOND_TO_MS(x) (x * 1000)
#define MS_TO_SECOND(x) (x / 1000.0)

void timer_init(bool, size_t);
void timer_set_verbose(bool _verbose);
void timer_set_print_interval_ms(size_t _interval);
void timer_set_print_interval_seconds(size_t _interval);

#endif
