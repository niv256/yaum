#include <etc/modules.h>
#include <etc/panic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MDL_PATH      "/modules/"
#define MDL_TEXT_PATH (MDL_PATH "text/")
#define MDL_EXEC_PATH (MDL_PATH "executables/")
#define MDL_LOGO      "logo.txt"

typedef uint32_t (*func)(void);

static size_t get_module_index(const char *module_name, char *path);

size_t mods_count;
multiboot_module_t *mods;

void init_modules(multiboot_info_t *mbt) {
  mods_count = (size_t)mbt->mods_count;
  mods       = (multiboot_module_t *)mbt->mods_addr;
}

static size_t get_module_index(const char *module_name, char *path) {
  for (size_t i = 0; i < mods_count; i++) {
    if (strcmp((char *)mods[i].cmdline + strlen(path), module_name)) {
      return i;
    }
  }
  return -1;
}

int print_module(const char *module_name) {
  size_t index = get_module_index(module_name, MDL_TEXT_PATH);
  if (index == -1) {
    return 1;
  }

  uint32_t mod_start = mods[index].mod_start;
  uint32_t mod_end   = mods[index].mod_end;
  size_t len         = mod_end - mod_start;

  for (size_t i = 0; i < len; i++) {
    putchar(((char *)mod_start)[i]);
  }
  return 0;
}

void write_logo(void) {
  if (print_module(MDL_LOGO)) {
    PANIC("yaum isodir/modules/logo.txt missing");
  }
}

int execute_module(const char *module_name, uint32_t *ret) {
  size_t index = get_module_index(module_name, MDL_EXEC_PATH);
  if (index == -1) {
    return 1;
  }

  func mod_start = (func)mods[index].mod_start;
  *ret           = mod_start();
  return 0;
}
