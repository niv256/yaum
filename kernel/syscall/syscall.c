#include <arch/i386/isr.h>
#include <mm/paging.h>
#include <stdio.h>
#include <syscall/syscall.h>

typedef struct syscall_args {
  uint32_t ebx;
  uint32_t ecx;
  uint32_t edx;
  uint32_t esi;
  uint32_t edi;
} syscall_args_t;

typedef int (*syscall_t)(syscall_args_t);

static int very_important_syscall(syscall_args_t args);
static void syscall(registers_t *regs);

// TODO: when userspace is solid, there should be a kernel stack for every
// process
uint8_t syscall_stack[PAGE_SIZE];

syscall_t syscall_table[SYSCALLS] = {very_important_syscall};

void init_syscall(void) {
  setup_isr_callback(SYSCALL_INT, (isr_t)syscall);
}

static int very_important_syscall(syscall_args_t args) {
  printf("very important syscall called!\nebx:\n0x%x\n", args.ebx);
  return 0xdeadbeef;
}

static void syscall(registers_t *regs) {
  uint32_t syscall_num = regs->eax;
  syscall_args_t args = {regs->ebx, regs->ecx, regs->edx, regs->esi, regs->edi};

  if (syscall_num < SYSCALLS && syscall_table[syscall_num]) {
    regs->eax = syscall_table[syscall_num](args);
  } else {
    printf("invalid syscall number: 0x%x\n", syscall_num);
    regs->eax = -1;
  }
}
