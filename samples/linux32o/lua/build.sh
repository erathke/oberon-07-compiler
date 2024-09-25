#/bin/bash

CC="cc"
CFLAGS="-m32 -no-pie"
COPTS="-nostartfiles -Wl,--gc-sections"
LIBS="liblua-i686-posix.a"
#LIBS="liblua-i686-linux.a"
DEF="-def API_sys"
OPTS="-entry _start -rtl RTL_sys"
OBC="../../../compilerX"

mkdir -p bin;
$OBC $1.ob07 linux32o $DEF $OPTS && 
	$CC $CFLAGS $COPTS -o bin/$1 $1.xo $LIBS -lm
