OBJECTS=

OBJECTS+=arch/i386/asmisr.o
OBJECTS+=arch/i386/asmpaging.o
OBJECTS+=arch/i386/descriptors.o
OBJECTS+=arch/i386/gdt.o
OBJECTS+=arch/i386/idt.o
OBJECTS+=arch/i386/isr.o
OBJECTS+=arch/i386/pmode.o

OBJECTS+=boot/boot.o

OBJECTS+=etc/kargs.o
OBJECTS+=etc/modules.o
OBJECTS+=etc/panic.o
OBJECTS+=etc/shutdown.o
OBJECTS+=etc/timer.o
OBJECTS+=etc/tools.o

OBJECTS+=io/screen.o
OBJECTS+=io/keyboard.o
OBJECTS+=io/shell.o
OBJECTS+=io/uart.o

OBJECTS+=kernel/kmain.o

OBJECTS+=mm/paging.o
OBJECTS+=mm/malloc.o
