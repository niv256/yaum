#ifndef MODULES_H
#define MODULES_H

#include <multiboot.h>
#include <stddef.h>
#include <stdint.h>

void init_modules(multiboot_info_t *mbt);
int print_module(const char *module_name);
void write_logo(void);
int execute_module(const char *module_name, uint32_t *ret);

#endif
