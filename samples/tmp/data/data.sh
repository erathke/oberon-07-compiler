#!/bin/bash

CC=gcc
CFLAGS="-m32 -nostartfiles -no-pie"
OBC="../../../compilerX"
FASM="../../../fasm"
LD="ld"
DEF="-def API_sys"
OPTS="-entry _start -rtl RTL_sys"
BINDIR="bin"
LIBDIR="lib"

mkdir -p $BINDIR $LIBDIR;

#$FASM data.asm $LIBDIR/data.o &&
$CC -o $LIBDIR/data.o -c data.c && \
$OBC Data.ob07 linux32o -out $LIBDIR/Data.xo $DEF $OPTS &&
	$CC $CFLAGS -o $BINDIR/data $LIBDIR/Data.xo $LIBDIR/data.o 

