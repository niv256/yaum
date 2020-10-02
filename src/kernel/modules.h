#ifndef MODULES_H
#define MODULES_H

#include "../include/stdint.h"
#include "multiboot.h"

void init_modules(multiboot_info_t *mbt);
int print_text_module(uint8_t index);
void write_logo(void);

enum err_codes { INVARG = 1 };

#endif
