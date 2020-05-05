#include <stdint.h>
#include "descriptors.h"

#define HARD_CODED_ENTRIES 5
#define SAVED_SPACE_FOR_ENTRIES 3
#define TOTAL_ENTRIES (HARD_CODED_ENTRIES + SAVED_SPACE_FOR_ENTRIES)

extern void gdt_write(uint32_t);

struct gdt_entry {
	uint16_t limit_first_16;
	uint16_t base_first_16;
	uint8_t base_middle_8;
	uint8_t access_byte;
	uint8_t limit_last_4_flags;
	uint8_t base_last_8;
} __attribute__((packed));
typedef struct gdt_entry gdt_entry;

static gdt_entry create_gdt_entry(uint32_t base, uint32_t limit,uint8_t access_byte, uint8_t flags);

struct gdt_ptr {
	uint16_t size;
	uint32_t offset;
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr;


static gdt_entry create_gdt_entry(uint32_t base, uint32_t limit,uint8_t access_byte, uint8_t flags){
	gdt_entry entry_to_fill;

	// limit checking:
	if (limit > 0xFFFFF) {
		// TODO: print error or something
	}

	entry_to_fill.limit_first_16 = limit & 0xFFFF;
	entry_to_fill.base_first_16 = base & 0xFFFF;
	entry_to_fill.base_middle_8 = (base & 0xFF0000) >> 16;
	entry_to_fill.access_byte = access_byte;
	entry_to_fill.limit_last_4_flags = (limit & 0x0F0000) >> 16;
	entry_to_fill.limit_last_4_flags |= flags & 0xF0;
	entry_to_fill.base_last_8 = (base & 0xFF000000) >> 24;

	return entry_to_fill;
}

void gdt_init(void){
	// 5 entries for now, save space for 3
	gdt_entry entries[HARD_CODED_ENTRIES + SAVED_SPACE_FOR_ENTRIES];
	gdt_ptr ptr_to_gdt;
	ptr_to_gdt.size = sizeof(gdt_entry)*TOTAL_ENTRIES - 1;
	ptr_to_gdt.offset = (uint32_t) &entries;

	// fill the entries
	entries[0] = create_gdt_entry(0, 0, 0, 0);		// null entry
	entries[1] = create_gdt_entry(0, 0xFFFFF, 0x9A, 0xCF);	// kernel code
	entries[2] = create_gdt_entry(0, 0xFFFFF, 0x92, 0xCF);	// kernel data
	entries[3] = create_gdt_entry(0, 0xFFFFF, 0xFA, 0xCF);	// user code
	entries[4] = create_gdt_entry(0, 0xFFFFF, 0xF2, 0xCF);	// user data

	gdt_write((uint32_t) &ptr_to_gdt);
}
