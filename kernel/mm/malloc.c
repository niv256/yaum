#include <etc/panic.h>
#include <io/screen.h>
#include <math.h>
#include <mm/malloc.h>
#include <stddef.h>

static char get_bit(size_t idx);
static void set_bit(size_t idx);
static void unset_bit(size_t idx);
static size_t find_cave(size_t count);
static void set_range(size_t start, size_t count);
static void unset_range(size_t start, size_t count);
static void add_alloc(size_t idx, size_t size);
static void remove_alloc(size_t idx);
static size_t first_inactive_alloc(void);
static size_t find_alloc(size_t idx);
static void __alloc(size_t start, size_t buckets);
static void __free(size_t idx);

heap_t heap;
/*
 * 1 - taken
 * 0 - free
 */
bitmap_t bitmap;
allocs_t allocs;

static char get_bit(size_t idx) {
  // return (bitmap >> (BITMAP_SIZE - idx)) & 1;
  return (bitmap >> idx) & 1;
}

static void set_bit(size_t idx) {
  // bitmap |= 1 << (BITMAP_SIZE - 1 - idx);
  bitmap |= 1 << idx;
}

static void unset_bit(size_t idx) {
  // bitmap &= ~(1 >> idx);
  bitmap &= ~(1 << idx);
}

static size_t find_cave(size_t count) {
  size_t cur   = 0;
  size_t start = 0;
  size_t idx   = 0;

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

static void set_range(size_t start, size_t count) {
  for (size_t i = start; i < start + count; i++) {
    set_bit(i);
  }
}

static void unset_range(size_t start, size_t count) {
  for (size_t i = start; i < start + count; i++) {
    unset_bit(i);
  }
}

static void add_alloc(size_t idx, size_t size) {
  size_t i = first_inactive_alloc();

  allocs[i].active = 1;
  allocs[i].idx    = idx;
  allocs[i].size   = size;
}

static void remove_alloc(size_t idx) {
  size_t i         = find_alloc(idx);
  allocs[i].active = 0;
}

static size_t first_inactive_alloc(void) {
  size_t i;
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

static size_t find_alloc(size_t idx) {
  size_t i;
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

void *kmalloc(size_t size) {
  if (size < BUCKET_SIZE) {
    size = BUCKET_SIZE;
  }

  size_t buckets = (size_t)ceil((float)size / BUCKET_SIZE);

  char start = find_cave(buckets);
  if (start == -1) {
    return NULL;
  }

  __alloc(start, buckets);
  return heap + start * BUCKET_SIZE;
}

static void __alloc(size_t start, size_t buckets) {
  set_range(start, buckets);
  add_alloc(start, buckets);
}

void kfree(void *ptr) {
  size_t idx = (size_t)((char *)ptr - heap) / BUCKET_SIZE;
  __free(idx);
}

static void __free(size_t idx) {
  size_t i = find_alloc(idx);
  unset_range(idx, allocs[i].size);
  remove_alloc(i);
}
