#ifndef MODULES_H
#define MODULES_H

#include <multiboot.h>
#include <stdint.h>

void init_modules(multiboot_info_t *mbt);
int get_module_index(const char *module_name);
int get_exec_module_index(const char *module_name);
int print_text_module(uint8_t index);
void write_logo(void);
int execute_binary_modules(uint8_t index);

#endif
