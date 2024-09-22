#/bin/bash

CC="gcc"
CFLAGS="-m32 -no-pie"
COPTIONS="-nostartfiles"
LIBS="liblua-i686-posix.a"
#LIBS="liblua-i686-linux.a"
#DEF="-def API_DEBUG"
#OPTS="-stk 1"

mkdir -p bin;
../../../compilerX $1.ob07 linux32o $DEF $OPTS && 
	$CC $CFLAGS $COPTIONS -o bin/$1 $1.xo $LIBS -lm
