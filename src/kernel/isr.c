#include "isr.h"
#include "screen.h"

void isr_handler(struct registers registers) {
	terminal_writestring("got interrupt");
	terminal_writeint(registers.int_num, 16);
	terminal_putchar('\n');
}
