#include <arch/i386/descriptors.h>
#include <etc/magic.h>
#include <etc/modules.h>
#include <etc/timer.h>
#include <io/keyboard.h>
#include <io/screen.h>
#include <mm/paging.h>
#include <stdio.h>
#include <syscall/syscall.h>

#if defined(__linux__) || !defined(__i686__)
#error "Either not using a cross-compiler or not an x86 elf compiler"
#endif

extern void jump_usermode(uint32_t);
extern void userspace_func(void);

int kmain(multiboot_info_t *mbt, uint32_t magic) {
  terminal_initialize();

  validate_magic(magic);

  init_modules(mbt);
  write_logo();
  putchar('\n');

  puts("screen initialized.");
  puts("modules initialized.");

  gdt_init();
  puts("gdt initialized.");

  tss_init();
  puts("tss initialized.");

  enter_pmode();
  puts("entered protected mode.");

  init_paging();
  puts("paging initialized.");

  idt_init();
  puts("idt initialized.");

  timer_init(TIMER_SILENT, SECOND_TO_MS(2));
  puts("timer initialized.");

  init_syscall();
  puts("syscalls initialized.");

  keyboard_init();
  puts("keyboard initialized.");

  puts("\n\njumping to user space:");
  jump_usermode((uint32_t)userspace_func);

  printf("\nshell:\n> ");

  for (;;)
    ;

  return 0;
}
