LD=ld
LDFLAGS=-melf_i386 -T linker.ld --build-id=none
OBC=../../../compilerX
FASM=../../../fasm
DEF=-def API_sys
OPTS=-entry kernelMain -rtl RTL_metal
KERNEL_DIR=bin
ISODIR=isodir
QEMU=qemu-system-i386
QEMU_OPTS=-enable-kvm -vga cirrus -m 32M -no-reboot


$(KERNEL_DIR)/loader.o:
	$(FASM) loader.asm $@


$(KERNEL_DIR)/Kernel.xo:
	$(OBC) Kernel.ob07 linux32o $(DEF) $(OPTS) -out $@


kernel: $(KERNEL_DIR)/loader.o $(KERNEL_DIR)/Kernel.xo
	@mkdir -p $(KERNEL_DIR)
	$(LD) $(LDFLAGS) $^ -o $(KERNEL_DIR)/kernel


clean:
	$(RM) $(KERNEL_DIR)/*


run: kernel
	 $(QEMU) $(QEMU_OPTS) -kernel $(KERNEL_DIR)/kernel


iso: kernel
	cp $(KERNEL_DIR)/kernel $(ISODIR)/boot
	grub-mkrescue -o $(KERNEL_DIR)/kernel.iso isodir
