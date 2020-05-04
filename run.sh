#!/bin/sh

cd src
make
cp untitled_niv_os.bin ../isodir/boot/untitled_niv_os.bin
make clean
cd ..
grub-mkrescue -o untitled_niv_os.iso isodir
rm isodir/boot/untitled_niv_os.bin
qemu-system-x86_64 -cdrom untitled_niv_os.iso
