#include <arch/i386/descriptors.h>
#include <etc/bargs.h>
#include <etc/modules.h>
#include <etc/timer.h>
#include <io/keyboard.h>
#include <io/screen.h>
#include <io/uart.h>
#include <mm/paging.h>

#if defined(__linux__) || !defined(__i686__)
#error "Either not using a cross-compiler or not an x86 elf compiler"
#endif

int kmain(multiboot_info_t *mbt, uint32_t magic) {
  init_uart();
  init_bargs(mbt, magic);

  terminal_initialize();
  write_logo();

  gdt_init();
  terminal_writestring("gdt initialized.\n");

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
