#ifndef KARGS_H
#define KARGS_H

#include "multiboot.h"
#include <stdint.h>

void init_kargs(multiboot_info_t *mbt, uint32_t magic);

#endif
