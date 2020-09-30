cd src
make
cp yaum.bin ../isodir/kernel/yaum.bin
make clean
cd ..
mkisofs -R -input-charset utf8 -b boot/grub/stage2_eltorito -boot-info-table -no-emul-boot -boot-load-size 4 -o yaum.iso isodir
qemu-system-x86_64 -monitor stdio -cdrom yaum.iso
