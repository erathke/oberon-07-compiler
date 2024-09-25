#!/bin/bash


OBC="../../../compilerX"
DEF="-def API_sys"
OPTS="-entry kernel_main -rtl RTL_sys"
#OPTS="-entry _start -rtl RTL_sys"
OBJS="boot.o"
LD=ld

mkdir -p bin;
../../../fasm boot.asm boot.o &&
	$OBC $1.ob07 linux32o -out $1.xo $DEF $OPTS &&
	$LD -T./min.ld $1.xo $OBJS -o bin/$1

