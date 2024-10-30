OBC=../../../compilerX
FASM=../../../fasm
LD=ld
LDFLAGS=-T./linker.ld
CC=gcc
CFLAGS=-m32
DEF=-def API_sys
OPTS=-entry _start -rtl RTL_sys
BINDIR=bin
LIBDIR=lib

all: Test ProdCons Example StackTest

dirs: 
	@mkdir -p lib bin

libs: dirs $(LIBDIR)/ProdCons.xo $(LIBDIR)/Example.xo $(LIBDIR)/StackTest.xo $(LIBDIR)/Test.xo

$(LIBDIR)/%.xo: %.ob07
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

deps: dirs $(LIBDIR)/coroutines.o $(LIBDIR)/setjmp.o

$(LIBDIR)/%.o: %.asm
	$(FASM) $^ $@
	
Test: deps $(LIBDIR)/Test.xo
	$(LD) $(LDFLAGS) $(LIBDIR)/Test.xo $(LIBDIR)/coroutines.o $(LIBDIR)/setjmp.o -o $(BINDIR)/Test
	
ProdCons: deps $(LIBDIR)/ProdCons.xo
	$(LD) $(LDFLAGS) $(LIBDIR)/ProdCons.xo $(LIBDIR)/coroutines.o $(LIBDIR)/setjmp.o -o $(BINDIR)/ProdCons
	
Example: deps $(LIBDIR)/Example.xo
	$(LD) $(LDFLAGS) $(LIBDIR)/Example.xo $(LIBDIR)/coroutines.o $(LIBDIR)/setjmp.o -o $(BINDIR)/Example

StackTest: deps $(LIBDIR)/StackTest.xo
	$(LD) $(LDFLAGS) $(LIBDIR)/StackTest.xo $(LIBDIR)/coroutines.o $(LIBDIR)/setjmp.o -o $(BINDIR)/StackTest

coro_example:
	$(CC) $(CFLAGS) -o $(BINDIR)/coro_example coro_example.c

clean:
	$(RM) $(BINDIR)/* $(LIBDIR)/*.o $(LIBDIR)/*.xo
	
