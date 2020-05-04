CC:=i686-elf-gcc
LD:=i686-elf-ld
ASM:=nasm
CC_FLAGS:=-Wall -ffreestanding -O2 -Wextra -std=gnu99 -c
LD_FLAGS:=-T linker.ld -ffreestanding -O2 -nostdlib -lgcc
ASM_FLAGS:=-felf32

all: kernel.o boot.o
	$(CC) $(LD_FLAGS) kernel.o boot.o -o untitled_niv_os.bin

kernel.o:
	$(CC) $(CC_FLAGS) kernel/kernel.c -o kernel.o

boot.o: kernel.o
	$(ASM) $(ASM_FLAGS) -o boot.o boot/boot.asm

clean:
	$(shell rm -rf *.o untitled_niv_os.bin)
