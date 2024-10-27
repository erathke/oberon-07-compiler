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
$FASM setjmp.asm $LIBDIR/setjmp.o &&
$OBC $1.ob07 linux32o -out $LIBDIR/$1.xo $DEF $OPTS &&
	$LD -T./linker.ld $LIBDIR/$1.xo $LIBDIR/coroutines.o $LIBDIR/setjmp.o -o bin/$1

