#!/bin/bash

rm Test
#../../compilerX TestLib.ob07 linux32o -out test.o && \
#../../compilerX TestLib2.ob07 linux32so -out libtest2.so && \
#../../compilerX Test.ob07 linux32o && gcc -no-pie -o Test boot.o Test.xo
#	../../compilerX Test.ob07 linux32o && gcc -no-pie -o Test test.o Test.xo
../../compilerX Test.ob07 linux32o && gcc -no-pie -o Test Test.xo
#../../compilerX Test.ob07 linux32o && gcc -o Test Test.xo

