#/bin/bash

CC="cc"
CFLAGS="-m32 -no-pie"
COPTIONS="-nostartfiles -nostdlib"
#COPTIONS="-nostartfiles"
#DEF="-def API_DEBUG"

../../../compilerX Assert.ob07 linux32o $DEF && $CC $CFLAGS $COPTIONS -o Assert Assert.xo -Wl,-T./min.ld,--build-id=none
#../../../compilerX Assert.ob07 linux32o -def API_DEBUG && $CC $CFLAGS $COPTIONS -o Assert Assert.xo
#../../../compilerX Assert.ob07 linux32o && ld -T./min.ld Assert.xo -o Assert
#../../../compilerX Assert.ob07 linux32o  && $CC $CFLAGS $COPTIONS -o Assert Assert.xo
