#ifndef MALLOC_H
#define MALLOC_H

#include <stdint.h>

#define HEAP_SIZE   0x1000
#define BUCKET_SIZE 64
#define BITMAP_SIZE (HEAP_SIZE / BUCKET_SIZE)
#define ALLOCS      BITMAP_SIZE

typedef struct {
  char active;
  int idx;
  int size;
} alloc_t;

typedef char heap_t[HEAP_SIZE];
typedef uint64_t bitmap_t;
typedef alloc_t allocs_t[BITMAP_SIZE];

void *kmalloc(int size);
void kfree(void *ptr);

#endif
