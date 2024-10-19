#/bin/bash

DEF="-def API_sys"
OPTS="-entry _start -rtl RTL_sys"
OBC="../../../compilerX"
LD="ld"
LDFLAGS="-T min.ld --build-id=none"

$OBC Assert.ob07 linux32o $DEF $OPTS && 
	$LD $LDFLAGS Assert.xo -o Assert
