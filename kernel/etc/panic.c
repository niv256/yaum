#include <etc/panic.h>
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
    /* trace ebp and return adress of functions */
    uint32_t *ebp;
    uint32_t *ret;

    asm("movl %%ebp, %0;": "=r" (ebp)); //magic
    ebp = (int *) *ebp; //de-refrence once so we won't print the value of the backtrace function

    while(ebp != NULL) {
        ret = (int *) *(ebp + 1); //pointers fun
        printf("value of ebp is %p\t value of ret is %p\n", ebp, ret);

        ebp = (int *) *ebp;
    }

}
