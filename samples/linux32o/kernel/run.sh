#/bin/bash

#qemu-system-i386 -cdrom hello-kernel.iso
#MEMORY="16M"
#DEVICE="-device VGA,vgamem_mb=64"
OPTS="-vga cirrus -m 32M -no-reboot"
KERNEL_DIR="bin"

qemu-system-i386 $OPTS -kernel $KERNEL_DIR/kernel
