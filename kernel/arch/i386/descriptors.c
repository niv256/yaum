#include <arch/i386/descriptors.h>
#include <arch/i386/isr.h>
#include <etc/tools.h>
#include <io/keyboard.h>
#include <io/screen.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define NUMBER_IDT_ENTRIES 256
#define NUMBER_GDT_ENTRIES 6

#define DPL_KERNEL 0
#define DPL_USER   3

#define KERNEL_CODE_INDEX 1
#define KERNEL_DATA_INDEX 2
#define USER_CODE_INDEX   3
#define USER_DATA_INDEX   4

#define SELECTOR_SHIFT_AMOUNT 3

#define KERNEL_CODE_SELECTOR \
  ((KERNEL_CODE_INDEX << SELECTOR_SHIFT_AMOUNT) | DPL_KERNEL)
#define KERNEL_DATA_SELECTOR \
  ((KERNEL_DATA_INDEX << SELECTOR_SHIFT_AMOUNT) | DPL_KERNEL)
#define USER_CODE_SELECTOR \
  ((USER_CODE_INDEX << SELECTOR_SHIFT_AMOUNT) | DPL_USER)
#define USER_DATA_SELECTOR \
  ((USER_DATA_INDEX << SELECTOR_SHIFT_AMOUNT) | DPL_USER)

// declare the interrupt service routines
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
extern void isr48();
extern void isr49();
extern void isr50();
extern void isr51();
extern void isr52();
extern void isr53();
extern void isr54();
extern void isr55();
extern void isr56();
extern void isr57();
extern void isr58();
extern void isr59();
extern void isr60();
extern void isr61();
extern void isr62();
extern void isr63();
extern void isr64();
extern void isr65();
extern void isr66();
extern void isr67();
extern void isr68();
extern void isr69();
extern void isr70();
extern void isr71();
extern void isr72();
extern void isr73();
extern void isr74();
extern void isr75();
extern void isr76();
extern void isr77();
extern void isr78();
extern void isr79();
extern void isr80();
extern void isr81();
extern void isr82();
extern void isr83();
extern void isr84();
extern void isr85();
extern void isr86();
extern void isr87();
extern void isr88();
extern void isr89();
extern void isr90();
extern void isr91();
extern void isr92();
extern void isr93();
extern void isr94();
extern void isr95();
extern void isr96();
extern void isr97();
extern void isr98();
extern void isr99();
extern void isr100();
extern void isr101();
extern void isr102();
extern void isr103();
extern void isr104();
extern void isr105();
extern void isr106();
extern void isr107();
extern void isr108();
extern void isr109();
extern void isr110();
extern void isr111();
extern void isr112();
extern void isr113();
extern void isr114();
extern void isr115();
extern void isr116();
extern void isr117();
extern void isr118();
extern void isr119();
extern void isr120();
extern void isr121();
extern void isr122();
extern void isr123();
extern void isr124();
extern void isr125();
extern void isr126();
extern void isr127();
extern void isr128();
extern void isr129();
extern void isr130();
extern void isr131();
extern void isr132();
extern void isr133();
extern void isr134();
extern void isr135();
extern void isr136();
extern void isr137();
extern void isr138();
extern void isr139();
extern void isr140();
extern void isr141();
extern void isr142();
extern void isr143();
extern void isr144();
extern void isr145();
extern void isr146();
extern void isr147();
extern void isr148();
extern void isr149();
extern void isr150();
extern void isr151();
extern void isr152();
extern void isr153();
extern void isr154();
extern void isr155();
extern void isr156();
extern void isr157();
extern void isr158();
extern void isr159();
extern void isr160();
extern void isr161();
extern void isr162();
extern void isr163();
extern void isr164();
extern void isr165();
extern void isr166();
extern void isr167();
extern void isr168();
extern void isr169();
extern void isr170();
extern void isr171();
extern void isr172();
extern void isr173();
extern void isr174();
extern void isr175();
extern void isr176();
extern void isr177();
extern void isr178();
extern void isr179();
extern void isr180();
extern void isr181();
extern void isr182();
extern void isr183();
extern void isr184();
extern void isr185();
extern void isr186();
extern void isr187();
extern void isr188();
extern void isr189();
extern void isr190();
extern void isr191();
extern void isr192();
extern void isr193();
extern void isr194();
extern void isr195();
extern void isr196();
extern void isr197();
extern void isr198();
extern void isr199();
extern void isr200();
extern void isr201();
extern void isr202();
extern void isr203();
extern void isr204();
extern void isr205();
extern void isr206();
extern void isr207();
extern void isr208();
extern void isr209();
extern void isr210();
extern void isr211();
extern void isr212();
extern void isr213();
extern void isr214();
extern void isr215();
extern void isr216();
extern void isr217();
extern void isr218();
extern void isr219();
extern void isr220();
extern void isr221();
extern void isr222();
extern void isr223();
extern void isr224();
extern void isr225();
extern void isr226();
extern void isr227();
extern void isr228();
extern void isr229();
extern void isr230();
extern void isr231();
extern void isr232();
extern void isr233();
extern void isr234();
extern void isr235();
extern void isr236();
extern void isr237();
extern void isr238();
extern void isr239();
extern void isr240();
extern void isr241();
extern void isr242();
extern void isr243();
extern void isr244();
extern void isr245();
extern void isr246();
extern void isr247();
extern void isr248();
extern void isr249();
extern void isr250();
extern void isr251();
extern void isr252();
extern void isr253();
extern void isr254();
extern void isr255();

extern void gdt_write(uint32_t);
extern void tss_write(void);
extern void idt_write(uint32_t);
extern void enable_a20(void);
extern void set_pmode(void);

extern uint8_t syscall_stack[];

static void irq_init(void);
void watch(void);

struct gdt_entry {
  uint32_t limit_first_16 : 16;
  uint32_t base_first_24 : 24;

  // access byte
  uint32_t accessed : 1;
  uint32_t read_write : 1;
  uint32_t direction_conforming : 1;
  uint32_t executable : 1;
  uint32_t type : 1;
  uint32_t privilege : 2;
  uint32_t present : 1;

  uint32_t limit_last_4 : 4;

  // flags
  uint32_t always_0 : 2;
  uint32_t size : 1;
  uint32_t granularity : 1;

  uint32_t base_last_8 : 8;
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

struct gdt_ptr {
  uint16_t size;
  uint32_t offset;
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr;

struct tss_entry {
  uint16_t link;
  uint16_t rsvd1;
  uint32_t esp0;
  uint16_t ss0;
  uint16_t rsvd2;
  uint32_t esp1;
  uint16_t ss1;
  uint16_t rsvd3;
  uint32_t esp2;
  uint16_t ss2;
  uint16_t rsvd4;
  uint32_t cr3;
  uint32_t eip;
  uint32_t eflags;
  uint32_t eax;
  uint32_t ecx;
  uint32_t edx;
  uint32_t ebx;
  uint32_t esp;
  uint32_t ebp;
  uint32_t esi;
  uint32_t edi;
  uint16_t es;
  uint16_t rsvd5;
  uint16_t cs;
  uint16_t rsvd6;
  uint16_t ss;
  uint16_t rsvd7;
  uint16_t ds;
  uint16_t rsvd8;
  uint16_t fs;
  uint16_t rsvd9;
  uint16_t gs;
  uint16_t rsvd10;
  uint16_t ldtr;
  uint16_t rsvd11;
  uint16_t rsvd12;
  uint16_t iopb_offset;
} __attribute__((packed));
typedef struct tss_entry tss_entry_t;

struct tss_descriptor {
  uint32_t limit_first_16 : 16;
  uint32_t base_first_24 : 24;
  uint32_t always_1 : 1;
  uint32_t busy : 1;
  uint32_t always_0 : 1;
  uint32_t always_1_2 : 1;
  uint32_t always_0_2 : 1;
  uint32_t DPL : 2;
  uint32_t present : 1;
  uint32_t limit_last_4 : 4;
  uint32_t avail : 1;
  uint32_t always_0_3 : 2;
  uint32_t granularity : 1;
  uint32_t base_last_8 : 8;
} __attribute__((packed));
typedef struct tss_descriptor tss_descriptor_t;

struct idt_entry {
  uint32_t offset_first_16 : 16;
  uint32_t selector : 16;
  uint32_t always_0 : 8;
  uint32_t type : 4;
  uint32_t storage_segment : 1;
  uint32_t DPL : 2;
  uint32_t present : 1;
  uint32_t offset_last_16 : 16;
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;

struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr idt_ptr;

static void set_gdt_entry(gdt_entry_t *entry, uint32_t base, uint32_t limit,
                          bool accessed, bool read_write,
                          bool direction_conforming, bool executable, bool type,
                          uint8_t privilege, bool present, bool size,
                          bool granularity);

static void set_tss_descriptor(tss_descriptor_t *descriptor, uint32_t base,
                               uint32_t limit, bool busy, uint8_t DPL,
                               bool present, bool granularity);

static void set_idt_entry(idt_entry_t *entry, uint32_t offset,
                          uint16_t selector, uint8_t type, bool storage_segment,
                          uint8_t DPL, bool present);

gdt_entry_t gdt_entries[NUMBER_GDT_ENTRIES];
tss_entry_t tss_entry;
idt_entry_t idt_entries[NUMBER_IDT_ENTRIES];

static void set_gdt_entry(gdt_entry_t *entry, uint32_t base, uint32_t limit,
                          bool accessed, bool read_write,
                          bool direction_conforming, bool executable, bool type,
                          uint8_t privilege, bool present, bool size,
                          bool granularity) {
  entry->limit_first_16       = limit & 0xFFFF;
  entry->base_first_24        = base & 0xFFFFFF;
  entry->accessed             = accessed;
  entry->read_write           = read_write;
  entry->direction_conforming = direction_conforming;
  entry->executable           = executable;
  entry->type                 = type;
  entry->privilege            = privilege;
  entry->present              = present;
  entry->limit_last_4         = (limit >> (20 - 4)) & 0x0F;
  entry->always_0             = 0;
  entry->size                 = size;
  entry->granularity          = granularity;
  entry->base_last_8          = (base >> (32 - 8)) & 0xFF;
}

static void set_tss_descriptor(tss_descriptor_t *descriptor, uint32_t base,
                               uint32_t limit, bool busy, uint8_t DPL,
                               bool present, bool granularity) {
  descriptor->limit_first_16 = limit & 0xFFFF;
  descriptor->base_first_24  = base & 0xFFFFFF;
  descriptor->always_1       = 1;
  descriptor->busy           = busy;
  descriptor->always_0       = 0;
  descriptor->always_1_2     = 1;
  descriptor->always_0_2     = 0;
  descriptor->DPL            = DPL;
  descriptor->present        = present;
  descriptor->limit_last_4   = limit >> (32 - 4);
  descriptor->always_0_3     = 0;
  descriptor->granularity    = granularity;
  descriptor->base_last_8    = (base >> (32 - 8)) & 0xFF;
}

void gdt_init(void) {
  // fill the entries
  set_gdt_entry(&gdt_entries[0], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0); // null entry
  set_gdt_entry(&gdt_entries[1], 0, 0xFFFFFFFF, 0, 1, 0, 1, 1, DPL_KERNEL, 1, 1,
                1); // kernel code
  set_gdt_entry(&gdt_entries[2], 0, 0xFFFFFFFF, 0, 1, 0, 0, 1, DPL_KERNEL, 1, 1,
                1); // kernel data
  set_gdt_entry(&gdt_entries[3], 0, 0xFFFFFFFF, 0, 1, 0, 1, 1, DPL_USER, 1, 1,
                1); // user code
  set_gdt_entry(&gdt_entries[4], 0, 0xFFFFFFFF, 0, 1, 0, 0, 1, DPL_USER, 1, 1,
                1); // user data
  set_tss_descriptor((tss_descriptor_t *)&gdt_entries[5], (uint32_t)&tss_entry,
                     sizeof(tss_entry_t), 0, DPL_USER, 1,
                     0); // TSS
}

void tss_init(void) {
  tss_entry.ss0  = KERNEL_DATA_SELECTOR;     // kernel data
  tss_entry.esp0 = (uint32_t)&syscall_stack; // stack pointer for syscalls
  tss_entry.iopb_offset = sizeof(tss_entry_t);
}

void enter_pmode(void) {
  gdt_ptr ptr_to_gdt;
  ptr_to_gdt.size   = sizeof(gdt_entry_t) * NUMBER_GDT_ENTRIES - 1;
  ptr_to_gdt.offset = (uint32_t)&gdt_entries;

  asm("cli"); // sti only after loading idt to avoid triple faut
  gdt_write((uint32_t)&ptr_to_gdt);
  tss_write();
  set_pmode();
}

static void set_idt_entry(idt_entry_t *entry, uint32_t offset,
                          uint16_t selector, uint8_t type, bool storage_segment,
                          uint8_t DPL, bool present) {
  entry->offset_first_16 = offset & 0xFFFF;
  entry->selector        = selector;
  entry->always_0        = 0;
  entry->type            = type;
  entry->storage_segment = storage_segment;
  entry->DPL             = DPL;
  entry->present         = present;
  entry->offset_last_16  = (offset >> (32 - 16)) & 0xFFFF;
}

void idt_init(void) {
  idt_ptr ptr_to_idt;
  ptr_to_idt.limit = (uint16_t)sizeof(idt_entry_t) * NUMBER_IDT_ENTRIES - 1;
  ptr_to_idt.base  = (uint32_t)&idt_entries;

  // set all idt gates
  set_idt_entry(&idt_entries[0], (uint32_t)isr0, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[1], (uint32_t)isr1, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[2], (uint32_t)isr2, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[3], (uint32_t)isr3, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[4], (uint32_t)isr4, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[5], (uint32_t)isr5, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[6], (uint32_t)isr6, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[7], (uint32_t)isr7, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[8], (uint32_t)isr8, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[9], (uint32_t)isr9, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[10], (uint32_t)isr10, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[11], (uint32_t)isr11, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[12], (uint32_t)isr12, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[13], (uint32_t)isr13, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[14], (uint32_t)isr14, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[15], (uint32_t)isr15, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[16], (uint32_t)isr16, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[17], (uint32_t)isr17, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[18], (uint32_t)isr18, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[19], (uint32_t)isr19, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[20], (uint32_t)isr20, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[21], (uint32_t)isr21, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[22], (uint32_t)isr22, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[23], (uint32_t)isr23, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[24], (uint32_t)isr24, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[25], (uint32_t)isr25, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[26], (uint32_t)isr26, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[27], (uint32_t)isr27, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[28], (uint32_t)isr28, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[29], (uint32_t)isr29, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[30], (uint32_t)isr30, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[31], (uint32_t)isr31, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ0], (uint32_t)irq0, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ1], (uint32_t)irq1, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ2], (uint32_t)irq2, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ3], (uint32_t)irq3, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ4], (uint32_t)irq4, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ5], (uint32_t)irq5, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ6], (uint32_t)irq6, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ7], (uint32_t)irq7, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ8], (uint32_t)irq8, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ9], (uint32_t)irq9, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ10], (uint32_t)irq10, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ11], (uint32_t)irq11, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ12], (uint32_t)irq12, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ13], (uint32_t)irq13, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ14], (uint32_t)irq14, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[IRQ15], (uint32_t)irq15, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[48], (uint32_t)isr48, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[49], (uint32_t)isr49, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[50], (uint32_t)isr50, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[51], (uint32_t)isr51, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[52], (uint32_t)isr52, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[53], (uint32_t)isr53, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[54], (uint32_t)isr54, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[55], (uint32_t)isr55, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[56], (uint32_t)isr56, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[57], (uint32_t)isr57, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[58], (uint32_t)isr58, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[59], (uint32_t)isr59, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[60], (uint32_t)isr60, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[61], (uint32_t)isr61, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[62], (uint32_t)isr62, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[63], (uint32_t)isr63, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[64], (uint32_t)isr64, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[65], (uint32_t)isr65, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[66], (uint32_t)isr66, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[67], (uint32_t)isr67, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[68], (uint32_t)isr68, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[69], (uint32_t)isr69, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[70], (uint32_t)isr70, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[71], (uint32_t)isr71, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[72], (uint32_t)isr72, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[73], (uint32_t)isr73, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[74], (uint32_t)isr74, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[75], (uint32_t)isr75, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[76], (uint32_t)isr76, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[77], (uint32_t)isr77, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[78], (uint32_t)isr78, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[79], (uint32_t)isr79, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[80], (uint32_t)isr80, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[81], (uint32_t)isr81, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[82], (uint32_t)isr82, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[83], (uint32_t)isr83, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[84], (uint32_t)isr84, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[85], (uint32_t)isr85, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[86], (uint32_t)isr86, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[87], (uint32_t)isr87, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[88], (uint32_t)isr88, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[89], (uint32_t)isr89, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[90], (uint32_t)isr90, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[91], (uint32_t)isr91, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[92], (uint32_t)isr92, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[93], (uint32_t)isr93, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[94], (uint32_t)isr94, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[95], (uint32_t)isr95, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[96], (uint32_t)isr96, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[97], (uint32_t)isr97, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[98], (uint32_t)isr98, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[99], (uint32_t)isr99, KERNEL_CODE_SELECTOR, 0xf, 0,
                DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[100], (uint32_t)isr100, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[101], (uint32_t)isr101, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[102], (uint32_t)isr102, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[103], (uint32_t)isr103, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[104], (uint32_t)isr104, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[105], (uint32_t)isr105, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[106], (uint32_t)isr106, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[107], (uint32_t)isr107, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[108], (uint32_t)isr108, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[109], (uint32_t)isr109, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[110], (uint32_t)isr110, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[111], (uint32_t)isr111, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[112], (uint32_t)isr112, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[113], (uint32_t)isr113, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[114], (uint32_t)isr114, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[115], (uint32_t)isr115, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[116], (uint32_t)isr116, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[117], (uint32_t)isr117, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[118], (uint32_t)isr118, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[119], (uint32_t)isr119, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[120], (uint32_t)isr120, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[121], (uint32_t)isr121, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[122], (uint32_t)isr122, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[123], (uint32_t)isr123, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[124], (uint32_t)isr124, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[125], (uint32_t)isr125, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[126], (uint32_t)isr126, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[127], (uint32_t)isr127, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);

  // syscall
  set_idt_entry(&idt_entries[128], (uint32_t)isr128, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_USER, 1);

  set_idt_entry(&idt_entries[129], (uint32_t)isr129, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[130], (uint32_t)isr130, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[131], (uint32_t)isr131, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[132], (uint32_t)isr132, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[133], (uint32_t)isr133, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[134], (uint32_t)isr134, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[135], (uint32_t)isr135, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[136], (uint32_t)isr136, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[137], (uint32_t)isr137, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[138], (uint32_t)isr138, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[139], (uint32_t)isr139, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[140], (uint32_t)isr140, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[141], (uint32_t)isr141, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[142], (uint32_t)isr142, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[143], (uint32_t)isr143, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[144], (uint32_t)isr144, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[145], (uint32_t)isr145, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[146], (uint32_t)isr146, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[147], (uint32_t)isr147, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[148], (uint32_t)isr148, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[149], (uint32_t)isr149, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[150], (uint32_t)isr150, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[151], (uint32_t)isr151, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[152], (uint32_t)isr152, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[153], (uint32_t)isr153, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[154], (uint32_t)isr154, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[155], (uint32_t)isr155, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[156], (uint32_t)isr156, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[157], (uint32_t)isr157, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[158], (uint32_t)isr158, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[159], (uint32_t)isr159, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[160], (uint32_t)isr160, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[161], (uint32_t)isr161, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[162], (uint32_t)isr162, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[163], (uint32_t)isr163, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[164], (uint32_t)isr164, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[165], (uint32_t)isr165, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[166], (uint32_t)isr166, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[167], (uint32_t)isr167, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[168], (uint32_t)isr168, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[169], (uint32_t)isr169, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[170], (uint32_t)isr170, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[171], (uint32_t)isr171, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[172], (uint32_t)isr172, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[173], (uint32_t)isr173, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[174], (uint32_t)isr174, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[175], (uint32_t)isr175, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[176], (uint32_t)isr176, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[177], (uint32_t)isr177, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[178], (uint32_t)isr178, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[179], (uint32_t)isr179, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[180], (uint32_t)isr180, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[181], (uint32_t)isr181, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[182], (uint32_t)isr182, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[183], (uint32_t)isr183, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[184], (uint32_t)isr184, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[185], (uint32_t)isr185, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[186], (uint32_t)isr186, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[187], (uint32_t)isr187, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[188], (uint32_t)isr188, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[189], (uint32_t)isr189, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[190], (uint32_t)isr190, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[191], (uint32_t)isr191, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[192], (uint32_t)isr192, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[193], (uint32_t)isr193, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[194], (uint32_t)isr194, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[195], (uint32_t)isr195, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[196], (uint32_t)isr196, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[197], (uint32_t)isr197, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[198], (uint32_t)isr198, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[199], (uint32_t)isr199, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[200], (uint32_t)isr200, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[201], (uint32_t)isr201, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[202], (uint32_t)isr202, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[203], (uint32_t)isr203, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[204], (uint32_t)isr204, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[205], (uint32_t)isr205, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[206], (uint32_t)isr206, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[207], (uint32_t)isr207, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[208], (uint32_t)isr208, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[209], (uint32_t)isr209, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[210], (uint32_t)isr210, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[211], (uint32_t)isr211, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[212], (uint32_t)isr212, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[213], (uint32_t)isr213, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[214], (uint32_t)isr214, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[215], (uint32_t)isr215, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[216], (uint32_t)isr216, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[217], (uint32_t)isr217, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[218], (uint32_t)isr218, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[219], (uint32_t)isr219, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[220], (uint32_t)isr220, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[221], (uint32_t)isr221, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[222], (uint32_t)isr222, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[223], (uint32_t)isr223, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[224], (uint32_t)isr224, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[225], (uint32_t)isr225, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[226], (uint32_t)isr226, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[227], (uint32_t)isr227, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[228], (uint32_t)isr228, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[229], (uint32_t)isr229, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[230], (uint32_t)isr230, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[231], (uint32_t)isr231, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[232], (uint32_t)isr232, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[233], (uint32_t)isr233, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[234], (uint32_t)isr234, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[235], (uint32_t)isr235, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[236], (uint32_t)isr236, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[237], (uint32_t)isr237, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[238], (uint32_t)isr238, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[239], (uint32_t)isr239, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[240], (uint32_t)isr240, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[241], (uint32_t)isr241, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[242], (uint32_t)isr242, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[243], (uint32_t)isr243, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[244], (uint32_t)isr244, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[245], (uint32_t)isr245, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[246], (uint32_t)isr246, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[247], (uint32_t)isr247, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[248], (uint32_t)isr248, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[249], (uint32_t)isr249, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[250], (uint32_t)isr250, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[251], (uint32_t)isr251, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[252], (uint32_t)isr252, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[253], (uint32_t)isr253, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[254], (uint32_t)isr254, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);
  set_idt_entry(&idt_entries[255], (uint32_t)isr255, KERNEL_CODE_SELECTOR, 0xf,
                0, DPL_KERNEL, 1);

  // write the idt to the cpu
  idt_write((uint32_t)&ptr_to_idt);

  // setup the irq, then enable interrupts
  irq_init();
  __asm__("sti");
}

static void irq_init(void) {
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);
}
