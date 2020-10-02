#include "modules.h"
#include "panic.h"
#include "screen.h"
#include <stdint.h>

uint32_t mods_count;
multiboot_module_t *mods;

enum modules { MDL_LOGO };

void init_modules(multiboot_info_t *mbt) {
  mods_count = mbt->mods_count;
  mods       = (multiboot_module_t *)mbt->mods_addr;
}

int print_text_module(uint8_t index) {
  if (index >= mods_count) {
    return INVARG;
  }
  uint32_t mod_start = mods[index].mod_start;
  uint32_t mod_end   = mods[index].mod_end;
  terminal_write((char *)mod_start, mod_end - mod_start);
  return 0;
}

void write_logo(void) {
  if (print_text_module(MDL_LOGO)) {
    PANIC("yaum isodir/modules/logo.txt missing");
  }
}
