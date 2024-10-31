#!/bin/bash

OBC="../../../compilerX"
FASM="../../../fasm"
CC="gcc"
CFLAGS="-m32 -no-pie -nostartfiles"
DEF="-def API_sys"
OPTS="-entry _start -rtl RTL_sys"
BINDIR="bin"
LIBDIR="lib"

mkdir -p $BINDIR $LIBDIR;

$CC -m32 -c segfault.c -o $LIBDIR/segfault.o;

$FASM coroutines.asm $LIBDIR/coroutines.o && \
	$FASM setjmp.asm $LIBDIR/setjmp.o && \
	$OBC $1.ob07 linux32o -out $LIBDIR/$1.xo $DEF $OPTS && \
	$CC $CFLAGS -o bin/$1 $LIBDIR/$1.xo $LIBDIR/coroutines.o $LIBDIR/setjmp.o $LIBDIR/segfault.o

