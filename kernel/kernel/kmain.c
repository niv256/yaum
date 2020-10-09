#include <arch/i386/descriptors.h>
#include <etc/magic.h>
#include <etc/modules.h>
#include <etc/timer.h>
#include <io/keyboard.h>
#include <io/screen.h>
#include <mm/paging.h>

#if defined(__linux__) || !defined(__i686__)
#error "Either not using a cross-compiler or not an x86 elf compiler"
#endif

int kmain(multiboot_info_t *mbt, uint32_t magic) {
  terminal_initialize();

  validate_magic(magic);

  init_modules(mbt);
  write_logo();
  terminal_newline();

  terminal_writestring("screen initialized.\n");
  terminal_writestring("modules initialized.\n");

  gdt_init();
  terminal_writestring("gdt initialized.\n");

  tss_init();
  terminal_writestring("tss initialized.\n");

  enter_pmode();
  terminal_writestring("entered protected mode.\n");

  init_paging();
  terminal_writestring("paging initialized.\n");

  idt_init();
  terminal_writestring("idt initialized.\n");

  timer_init(TIMER_SILENT, SECOND_TO_MS(2));
  terminal_writestring("timer initialized.\n");

  keyboard_init();
  terminal_writestring("keyboard initialized.\n");

  terminal_writestring("\nshell:\n> ");

  for (;;)
    ;

  return 0;
}
