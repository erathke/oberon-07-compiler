#/bin/bash

LDFLAGS="-T linker.ld --build-id=none"
DEF="-def API_sys"
OPTS="-entry kernelInit -rtl RTL_sys"
OBC="../../../compilerX"
FASM="../../../fasm"
KERNEL_DIR="bin"

#CC="gcc"
#CFLAGS="-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
#             -nostartfiles -nodefaultlibs -Wall -Wextra -Werror"
#$CC $CFLAGS -c interrupts.c -o interrupts.o && 
	
$FASM loader.asm loader.o && \
	$OBC $1.ob07 linux32o $DEF $OPTS && \
	ld -melf_i386 $LDFLAGS loader.o Kernel.xo -o $KERNEL_DIR/kernel
