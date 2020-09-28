#include "paging.h"
#include <stdint.h>

static void init_pd(void);
static void init_pt(void);
extern void set_paging(uint32_t);

page_table_t page_table;
page_directory_t page_directory;

void init_paging(void) {
  init_pd();
  init_pt();
  page_directory[0] = (uint32_t)page_table | PAGE_PRESENT | PAGE_USER;
  set_paging((uint32_t)&page_directory);
}

static void init_pd(void) {
  // blank pdes
  for (int i = 0; i < PDE_IN_DIRECTORY; i++) {
    page_directory[i] = PAGE_WRITE;
  }
}

static void init_pt(void) {
  for (int i = 0; i < PTE_IN_TABLE; i++) {
    // set frame as i
    page_table[i] = (i << (32 - 20)) | PAGE_PRESENT | PAGE_WRITE;
  }
}
