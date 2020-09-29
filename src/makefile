CC:=i686-elf-gcc
LD:=i686-elf-ld
ASM:=nasm
CC_FLAGS:=-c -Wall -ffreestanding
LD_FLAGS:=-T linker.ld
ASM_FLAGS:=-f elf

OBJECTS:=kernel.o boot.o descriptors.o screen.o isr.o asmisr.o gdt.o idt.o string.o stdlib.o tools.o keyboard.o shell.o ctype.o panic.o shutdown.o pmode.o paging.o asmpaging.o timer.o

all: kernel.o boot.o isr.o
	$(LD) $(LD_FLAGS) $(OBJECTS) -o untitled_niv_os.bin

kernel.o: descriptors.o screen.o keyboard.o paging.o timer.o
	$(CC) $(CC_FLAGS) kernel/kernel.c -o kernel.o

screen.o: string.o stdlib.o
	$(CC) $(CC_FLAGS) kernel/screen.c -o screen.o

string.o: ctype.o
	$(CC) $(CC_FLAGS) include/string.c -o string.o

stdlib.o:
	$(CC) $(CC_FLAGS) include/stdlib.c -o stdlib.o

ctype.o:
	$(CC) $(CC_FLAGS) include/ctype.c -o ctype.o

boot.o: kernel.o
	$(ASM) $(ASM_FLAGS) -o boot.o boot/boot.asm

descriptors.o: gdt.o pmode.o idt.o asmisr.o tools.o keyboard.o
	$(CC) $(CC_FLAGS) kernel/descriptors.c -o descriptors.o

keyboard.o: tools.o screen.o shell.o
	$(CC) $(CC_FLAGS) kernel/keyboard.c -o keyboard.o

shell.o: shutdown.o
	$(CC) $(CC_FLAGS) kernel/shell.c -o shell.o

shutdown.o:
	$(CC) $(CC_FLAGS) kernel/shutdown.c -o shutdown.o

gdt.o:
	$(ASM) $(ASM_FLAGS) -o gdt.o kernel/gdt.asm

pmode.o:
	$(ASM) $(ASM_FLAGS) -o pmode.o kernel/pmode.asm

idt.o:
	$(ASM) $(ASM_FLAGS) -o idt.o kernel/idt.asm

asmisr.o:
	$(ASM) $(ASM_FLAGS) -o asmisr.o kernel/asmisr.asm

isr.o: tools.o screen.o panic.o
	$(CC) $(CC_FLAGS) kernel/isr.c -o isr.o

tools.o:
	$(CC) $(CC_FLAGS) kernel/tools.c -o tools.o

panic.o: screen.o
	$(CC) $(CC_FLAGS) kernel/panic.c -o panic.o

paging.o: asmpaging.o
	$(CC) $(CC_FLAGS) kernel/paging.c -o paging.o

asmpaging.o:
	$(ASM) $(ASM_FLAGS) -o asmpaging.o kernel/asmpaging.asm

timer.o: isr.o screen.o
	$(CC) $(CC_FLAGS) kernel/timer.c -o timer.o

clean:
	$(shell rm -rf *.o untitled_niv_os.bin)
