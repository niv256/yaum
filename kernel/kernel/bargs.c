#include "bargs.h"
#include "modules.h"
#include "panic.h"

void init_bargs(multiboot_info_t *mbt, uint32_t magic) {
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    PANIC("boot magic number incorrect");
  }
  init_modules(mbt);
}
