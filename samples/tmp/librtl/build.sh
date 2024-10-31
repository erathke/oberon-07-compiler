#!/bin/bash
OBC="../../../compilerX" 
LD="ld"
LDFLAGS="-T min.ld --build-id=none"

$OBC $1.ob07 linux32o -out $1.xo -entry _start -rtl none && \
	$OBC lib/RTL_sys.ob07 linux32o -out lib/RTL_sys.xo -rtl none && \
	$LD $LDFLAGS lib/RTL_sys.xo $1.xo -o $1
