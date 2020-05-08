#include "isr.h"
#include "screen.h"

void isr_handler(struct registers registers) {
	terminal_writestring("got interrupt: ");
	terminal_writeint(registers.ds, 16);
	terminal_putchar('\n');
	return;
}
