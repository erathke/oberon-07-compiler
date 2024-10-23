#!/bin/bash

OBC="../../../compilerX"
FASM="../../../fasm"
LD="ld"
DEF="-def API_sys"
OPTS="-entry _start -rtl RTL_sys"
BINDIR="bin"
LIBDIR="lib"

mkdir -p $BINDIR $LIBDIR;

$FASM coroutines.asm $LIBDIR/coroutines.o &&
	$OBC $1.ob07 linux32o -out $LIBDIR/$1.xo $DEF $OPTS &&
	$LD -T./min.ld $LIBDIR/$1.xo $LIBDIR/coroutines.o -o bin/$1

