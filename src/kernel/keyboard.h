#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isr.h"

void get_key_press(registers_t regs);
void keyboard_init(void);

#endif
