#/bin/bash
FASM="../../../fasm"
#DEF="-def API_sys" 
OPTS="-entry _start -rtl RTL_sys"
OBC="../../../compilerX"
LD="ld"
LDFLAGS="-T min.ld --build-id=none"
CC="gcc -m32 -no-pie"

$CC -c avx.c -o avx_copy.o

$FASM avx.asm && \
    $OBC TestAVX.ob07 linux32o $DEF $OPTS && \
    $CC -Wpsabi -nostartfiles TestAVX.xo avx.o avx_copy.o -o TestAVX
#	$LD $LDFLAGS TestAVX.xo avx.o -o TestAVX
