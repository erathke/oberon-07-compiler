#!/bin/bash

CC=cc
MACHINE=`uname -m`
LIBS="./lib/libraylib-${MACHINE}.a"
INCLUDE="./include"
CFLAGS="-m32 -no-pie"
OBC="../../../compilerX"

rm $1.xo
$CC -c lib/glue.c -o glue.o -I$INCLUDE && $OBC $1.ob07 linux32o && \
	$CC $CFLAGS -o $1 $1.xo glue.o -I$INCLUDE $LIBS -lm

