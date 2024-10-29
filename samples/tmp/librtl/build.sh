#!/bin/bash
OBC="../../../compilerX" 
RTL=$2
ENTRY=$3

LD="ld"
LDFLAGS="-T min.ld --build-id=none"

$OBC $1.ob07 linux32o -out $1.xo -entry _start -rtl RTL_skel
$OBC RTL_sys.ob07 linux32o -out RTL_sys.xo -rtl RTL_def
