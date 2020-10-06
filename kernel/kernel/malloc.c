#include "malloc.h"
#include "panic.h"
#include "screen.h"
#include <kernel/math.h>
#include <stddef.h>

static char get_bit(char idx);
static void set_bit(char idx);
static void unset_bit(char idx);
static char find_cave(int count);
static void set_range(char start, char count);
static void unset_range(char start, char count);
static void add_alloc(int idx, int size);
static void remove_alloc(int idx);
static int first_inactive_alloc(void);
static int find_alloc(int idx);
static void __alloc(int start, int buckets);
static void __free(int idx);

heap_t heap;
/*
 * 1 - taken
 * 0 - free
 */
bitmap_t bitmap;
allocs_t allocs;

static char get_bit(char idx) {
  // return (bitmap >> (BITMAP_SIZE - idx)) & 1;
  return (bitmap >> idx) & 1;
}

static void set_bit(char idx) {
  // bitmap |= 1 << (BITMAP_SIZE - 1 - idx);
  bitmap |= 1 << idx;
}

static void unset_bit(char idx) {
  // bitmap &= ~(1 >> idx);
  bitmap &= ~(1 << idx);
}

static char find_cave(int count) {
  int cur   = 0;
  int start = 0;
  int idx   = 0;

  while (cur < count && idx < BITMAP_SIZE) {
    if (get_bit(idx++)) {
      cur   = 0;
      start = cur + 1;
    } else {
      cur++;
    }
  }

  if (cur != count) {
    return -1;
  }

  return start;
}

static void set_range(char start, char count) {
  for (int i = start; i < start + count; i++) {
    set_bit(i);
  }
}

static void unset_range(char start, char count) {
  for (int i = start; i < start + count; i++) {
    unset_bit(i);
  }
}

static void add_alloc(int idx, int size) {
  int i = first_inactive_alloc();

  allocs[i].active = 1;
  allocs[i].idx    = idx;
  allocs[i].size   = size;
}

static void remove_alloc(int idx) {
  int i            = find_alloc(idx);
  allocs[i].active = 0;
}

static int first_inactive_alloc(void) {
  int i;
  for (i = 0; i < ALLOCS; i++) {
    if (!allocs[i].active) {
      break;
    }
  }

  if (allocs[i].active) {
    PANIC("tried to add alloc when shouldn't have been possible");
  }

  return i;
}

static int find_alloc(int idx) {
  int i;
  for (i = 0; i < ALLOCS; i++) {
    if (allocs[i].idx == idx) {
      break;
    }
  }

  if (allocs[i].idx != idx) {
    PANIC("couldn't find alloc space when should have been able");
  }

  return i;
}

void *kmalloc(int size) {
  if (size < BUCKET_SIZE) {
    size = BUCKET_SIZE;
  }

  int buckets = (int)ceil((float)size / BUCKET_SIZE);

  char start = find_cave(buckets);
  if (start == -1) {
    return NULL;
  }

  __alloc(start, buckets);
  return heap + start * BUCKET_SIZE;
}

static void __alloc(int start, int buckets) {
  set_range(start, buckets);
  add_alloc(start, buckets);
}

void kfree(void *ptr) {
  int idx = (int)((char *)ptr - heap) / BUCKET_SIZE;
  __free(idx);
}

static void __free(int idx) {
  int i = find_alloc(idx);
  unset_range(idx, allocs[i].size);
  remove_alloc(i);
}
