LD=ld
LDFLAGS=-T linker.ld --build-id=none
OBC=../../../compilerX
FASM=../../../fasm
OPTS=-entry kernelMain -rtl none
KERNEL_DIR=bin
ISODIR=isodir
QEMU=qemu-system-i386
QEMU_OPTS=-enable-kvm -vga cirrus -m 32M -no-reboot
RTL_DIR=rtl
LIB_DIR=lib
LIBS=$(LIB_DIR)/libcoro.a

all: kernel run

dirs:
	@mkdir -p $(KERNEL_DIR) $(RTL_DIR)


$(KERNEL_DIR)/loader.o: dirs
	$(FASM) loader.asm $@


$(KERNEL_DIR)/Kernel.xo: dirs
	$(OBC) Kernel.ob07 linux32o $(OPTS) -out $@


kernel: $(RTL_DIR)/RTL_metal.xo $(KERNEL_DIR)/loader.o $(KERNEL_DIR)/Kernel.xo
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $(KERNEL_DIR)/kernel


$(RTL_DIR)/RTL_metal.xo: dirs
	cd $(RTL_DIR); ../$(OBC) RTL_metal.ob07 linux32o -rtl none -out RTL_metal.xo

rtl: $(RTL_DIR)/RTL_metal.xo


clean:
	$(RM) $(KERNEL_DIR)/* $(RTL_DIR)/RTL_metal.xo


run:
	 $(QEMU) $(QEMU_OPTS) -kernel $(KERNEL_DIR)/kernel


iso: kernel
	cp $(KERNEL_DIR)/kernel $(ISODIR)/boot
	grub-mkrescue -o $(KERNEL_DIR)/kernel.iso isodir
