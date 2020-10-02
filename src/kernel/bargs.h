#ifndef BARGS_H
#define BARGS_H

#include "multiboot.h"
#include <stdint.h>

void init_bargs(multiboot_info_t *mbt, uint32_t magic);

#endif
