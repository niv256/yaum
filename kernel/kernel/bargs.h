#ifndef BARGS_H
#define BARGS_H

#include <stdint.h>
#include "multiboot.h"

void init_bargs(multiboot_info_t *mbt, uint32_t magic);

#endif
