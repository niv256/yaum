#include "modules.h"
#include "panic.h"
#include "screen.h"
#include <kernel/stdlib.h>
#include <kernel/string.h>

#define MDL_PATH      "/modules/"
#define MDL_EXEC_PATH "/modules/executables/"
#define MDL_LOGO      "text/logo.txt"

typedef uint32_t (*func)(void);

static void validate_index(uint8_t index);

uint32_t mods_count;
multiboot_module_t *mods;

void init_modules(multiboot_info_t *mbt) {
  mods_count = mbt->mods_count;
  mods       = (multiboot_module_t *)mbt->mods_addr;
}

static void validate_index(uint8_t index) {
  if (index >= mods_count) {
    PANIC("invalid module index");
  }
}

int get_module_index(const char *module_name) {
  for (int i = 0; i < mods_count; i++) {
    if (strcmp((char *)mods[i].cmdline + strlen(MDL_PATH), module_name)) {
      return i;
    }
  }
  return -1;
}

int get_exec_module_index(const char *module_name) {
  for (int i = 0; i < mods_count; i++) {
    if (strcmp((char *)mods[i].cmdline + strlen(MDL_EXEC_PATH), module_name)) {
      return i;
    }
  }
  return -1;
}

int print_text_module(uint8_t index) {
  validate_index(index);

  uint32_t mod_start = mods[index].mod_start;
  uint32_t mod_end   = mods[index].mod_end;
  terminal_write((char *)mod_start, mod_end - mod_start);
  return 0;
}

void write_logo(void) {
  int module_index = get_module_index(MDL_LOGO);
  if (module_index == -1) {
    PANIC("yaum isodir/modules/logo.txt missing");
  }
  print_text_module(module_index);
}

int execute_binary_modules(uint8_t index) {
  validate_index(index);

  func mod_start = (func)mods[index].mod_start;
  return mod_start();
}
