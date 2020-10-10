#include <arch/i386/isr.h>
#include <etc/panic.h>
#include <mm/paging.h>
#include <stddef.h>
#include <stdio.h>

static void init_pd(void);
static void init_pt(void);
extern void set_paging(uint32_t);
static void page_fault(registers_t *regs);

page_table_t page_table;
page_directory_t page_directory;

void init_paging(void) {
  init_pd();
  init_pt();
  setup_isr_callback(0xe, page_fault);
  set_paging((uint32_t)&page_directory);
}

static void init_pd(void) {
  // blank pdes
  for (size_t i = 0; i < PDE_IN_DIRECTORY; i++) {
    page_directory[i] = PAGE_WRITE;
  }
  // page_directory[0] = (uint32_t)&page_table | PAGE_PRESENT | PAGE_USER;
  page_directory[0] =
      (uint32_t)&page_table | PAGE_PRESENT | PAGE_USER | PAGE_WRITE;
}

static void init_pt(void) {
  for (size_t i = 0; i < PTE_IN_TABLE; i++) {
    // set frame as i

    // TODO: really should not be user pages
    // page_table[i] = (i << (32 - 20)) | PAGE_PRESENT | PAGE_WRITE;
    page_table[i] = (i << (32 - 20)) | PAGE_PRESENT | PAGE_WRITE | PAGE_USER;
  }
}

static void page_fault(registers_t *regs) {
  uint32_t fault_addr;
  asm volatile("mov %%cr2, %0" : "=r"(fault_addr));

  union {
    struct {
      uint32_t present : 1;
      uint32_t write : 1;
      uint32_t user : 1;
      uint32_t reserved : 1;
    };
    uint32_t code;
  } err_code;
  err_code.code = regs->err_code;

  printf("page fault: (");
  if (err_code.present)
    printf("page not present, ");
  if (err_code.write)
    printf("read only page, ");
  if (err_code.user)
    printf("kernel mode only page, ");
  if (err_code.reserved)
    printf("reserved page, ");
  printf(") at address 0x%x\n", fault_addr);

  PANIC("page fault");
}
