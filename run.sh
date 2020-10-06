make
cp kernel/yaum.bin isodir/kernel/yaum.bin
mkisofs -R -input-charset utf8 -b boot/grub/stage2_eltorito -boot-info-table -no-emul-boot -boot-load-size 4 -o yaum.iso isodir
qemu-system-x86_64 -serial stdio -cdrom yaum.iso
