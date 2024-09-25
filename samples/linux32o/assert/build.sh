#/bin/bash

CC="cc"
CFLAGS="-m32 -no-pie"
LDFLAGS="-Wl,-T./min.ld,--build-id=none"
COPTS="-nostartfiles -nostdlib"
DEF="-def API_sys"
OPTS="-entry _start -rtl RTL_sys"
OBC="../../../compilerX"

$OBC $1.ob07 linux32o $DEF $OPTS && 
	$CC $CFLAGS $COPTS -o $1 $1.xo $LDFLAGS
