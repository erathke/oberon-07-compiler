#/bin/bash

CC="gcc"
#CC="i686-linux-gnu-gcc"
CFLAGS="-m32 -no-pie"
COPTIONS="-nostartfiles -Wl,--gc-sections"
#COPTIONS="-static -nostartfiles -Wl,--gc-sections"
LIBS="liblua-i686-posix.a"
#LIBS="liblua-i686-linux.a"
#DEF="-def API_DEBUG"
OPTS="-entry _start"
OBC="../../../compilerX"

mkdir -p bin;
$OBC $1.ob07 linux32o $DEF $OPTS && 
	$CC $CFLAGS $COPTIONS -o bin/$1 $1.xo $LIBS -lm
