#ifndef MODULES_H
#define MODULES_H

#include "multiboot.h"
#include <stdint.h>

void init_modules(multiboot_info_t *mbt);
int print_text_module(uint8_t index);
void write_logo(void);

enum err_codes { INVARG = 1 };

#endif
