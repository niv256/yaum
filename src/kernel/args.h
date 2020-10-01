#ifndef ARGS_H
#define ARGS_H

#include "multiboot.h"
#include <stdint.h>

void validate_args(multiboot_info_t *mbt, uint32_t magic);

#endif
