#ifndef _PAGING_H
#define _PAGING_H

#include <stdint.h>

#define PAGE_SIZE 0x1000

typedef uint32_t pte_t;
typedef uint32_t pde_t;

#define PTE_IN_TABLE     1024
#define PDE_IN_DIRECTORY 1024

typedef pte_t page_table_t[PTE_IN_TABLE] __attribute__((aligned(PAGE_SIZE)));
typedef pde_t page_directory_t[PDE_IN_DIRECTORY]
    __attribute__((aligned(PAGE_SIZE)));

#define PAGE_PRESENT 0x1
#define PAGE_WRITE   0x2
#define PAGE_USER    0x4

void init_paging(void);

#endif
