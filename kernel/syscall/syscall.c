#include <arch/i386/isr.h>
#include <io/screen.h>
#include <syscall/syscall.h>

static int very_important_syscall(void);
static void syscall(registers_t *regs);

typedef int (*syscall_t)(void);

syscall_t syscall_table[SYSCALLS] = {very_important_syscall};

void init_syscall(void) {
  setup_isr_callback(SYSCALL_INT, (isr_t)syscall);
}

static int very_important_syscall(void) {
  terminal_writestring("very important syscall called!\n");
  return 0xdeadbeef;
}

static void syscall(registers_t *regs) {
  uint32_t syscall_num = regs->eax;
  if (syscall_num < SYSCALLS && syscall_table[syscall_num]) {
    regs->eax = syscall_table[syscall_num]();
  } else {
    terminal_writestring("unknown syscall:\n");
    terminal_writehex(syscall_num);
    regs->eax = -1;
  }
}
