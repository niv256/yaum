#include <etc/panic.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static void print_info(void);

void panic(char *panic_msg, char *file, int line) {
  printf("\nPANIC: \"%s\" (%s:%d)\n", panic_msg, file, line);

  print_info();

  __asm__("cli");
  for (;;) {
    __asm__("hlt");
  }
}

static void print_info(void) {
  uint32_t *ebp;
  uint32_t *ret;

  asm("movl %%ebp, %0;" : "=r"(ebp));
  // skip first iteration
  ebp = (uint32_t *)*ebp;

  while (ebp != NULL) {
    printf("0x%p ", ebp[1]);

    ebp = (uint32_t *)ebp[0];
  }
}
