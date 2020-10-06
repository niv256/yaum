OBJECTS=

OBJECTS+=boot/boot.o

OBJECTS+=kernel/kmain.o
OBJECTS+=kernel/descriptors.o
OBJECTS+=kernel/screen.o
OBJECTS+=kernel/isr.o
OBJECTS+=kernel/asmisr.o
OBJECTS+=kernel/gdt.o
OBJECTS+=kernel/idt.o
OBJECTS+=kernel/tools.o
OBJECTS+=kernel/keyboard.o
OBJECTS+=kernel/shell.o
OBJECTS+=kernel/panic.o
OBJECTS+=kernel/shutdown.o
OBJECTS+=kernel/pmode.o
OBJECTS+=kernel/paging.o
OBJECTS+=kernel/asmpaging.o
OBJECTS+=kernel/timer.o
OBJECTS+=kernel/malloc.o
OBJECTS+=kernel/modules.o
OBJECTS+=kernel/bargs.o
OBJECTS+=kernel/uart.o
