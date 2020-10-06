#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <arch/i386/isr.h>

void get_key_press(registers_t regs);
void keyboard_init(void);

#endif
