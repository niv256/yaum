#ifndef MODULES_H
#define MODULES_H

#include <multiboot.h>
#include <stddef.h>
#include <stdint.h>

void init_modules(multiboot_info_t *mbt);
size_t get_module_index(const char *module_name);
size_t get_exec_module_index(const char *module_name);
int print_text_module(size_t index);
void write_logo(void);
int execute_binary_modules(size_t index);

#endif
