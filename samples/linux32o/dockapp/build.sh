#/bin/bash

CC="cc"
CFLAGS="-m32 -no-pie"
COPTS="-nostartfiles -Wl,--gc-sections"
LDFLAGS="-lX11 -ldockapp"
DEF="-def API_sys"
OPTS="-entry _start -rtl RTL_sys"
OBC="../../../compilerX"

mkdir -p bin;
$OBC $1.ob07 linux32o $DEF $OPTS && \
	$CC $CFLAGS -c lib/glue.c -o lib/glue.o && \
	$CC $CFLAGS $COPTS -o bin/$1 $1.xo lib/glue.o $LDFLAGS
