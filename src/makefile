CC:=i686-elf-gcc
LD:=i686-elf-ld
ASM:=nasm
CC_FLAGS:=-Wall -ffreestanding -O2 -Wextra -std=gnu99 -c
LD_FLAGS:=-T linker.ld -ffreestanding -O2 -nostdlib -lgcc
ASM_FLAGS:=-felf32

all: kernel.o boot.o
	$(CC) $(LD_FLAGS) kernel.o boot.o gdt.o descriptors.o screen.o string.o -o untitled_niv_os.bin

kernel.o: descriptors.o screen.o
	$(CC) $(CC_FLAGS) kernel/kernel.c -o kernel.o

screen.o: string.o
	$(CC) $(CC_FLAGS) kernel/screen.c -o screen.o

string.o:
	$(CC) $(CC_FLAGS) include/string.c -o string.o

boot.o: kernel.o
	$(ASM) $(ASM_FLAGS) -o boot.o boot/boot.asm

descriptors.o: gdt.o
	$(CC) $(CC_FLAGS) kernel/descriptors.c -o descriptors.o

gdt.o:
	$(ASM) $(ASM_FLAGS) -o gdt.o kernel/gdt.asm

clean:
	$(shell rm -rf *.o untitled_niv_os.bin)
