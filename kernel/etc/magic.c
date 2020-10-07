#include <etc/magic.h>
#include <etc/panic.h>
#include <multiboot.h>

void validate_magic(uint32_t magic) {
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    PANIC("boot magic number incorrect");
  }
}
