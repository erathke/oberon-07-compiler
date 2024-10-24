#!/bin/bash

OBC="../../../compilerX"
FASM="../../../fasm"
LD="ld"
DEF="-def API_sys"
OPTS="-entry _start -rtl RTL_sys"
BINDIR="bin"
LIBDIR="lib"

mkdir -p $BINDIR $LIBDIR;

$FASM data.asm $LIBDIR/data.o &&
$OBC Data.ob07 linux32o -out $LIBDIR/Data.xo $DEF $OPTS &&
	$LD -T./min.ld $LIBDIR/Data.xo $LIBDIR/data.o -o bin/data

