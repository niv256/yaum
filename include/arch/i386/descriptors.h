#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H

void enter_pmode(void);
void gdt_init(void);
void tss_init(void);
void idt_init(void);

#endif
