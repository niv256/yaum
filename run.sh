cd src
make
cp untitled_niv_os.bin ../isodir/kernel/untitled_niv_os.bin
make clean
cd ..
mkisofs -R -input-charset utf8 -b boot/grub/stage2_eltorito -boot-info-table -no-emul-boot -boot-load-size 4 -o untitled_niv_os.iso isodir
qemu-system-x86_64 -monitor stdio -cdrom untitled_niv_os.iso
