#!/bin/bash
CC="gcc"
CFLAGS="-no-pie"
../../../compilerX $1.ob07 linux32o -def linux32o && $CC $CFLAGS -o $1 $1.xo
