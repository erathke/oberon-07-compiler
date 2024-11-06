OBC=../../../compilerX
FASM=../../../fasm
LD=ld
LDFLAGS=-T./linker.ld
CC=gcc
CFLAGS=-m32
DEF=-def API_sys
OPTS=-entry _start -rtl none
BINDIR=bin
LIBDIR=lib
LIBS=$(LIBDIR)/libcoro.a

all: Test ProdCons Example StackTest Skynet

dirs: 
	@mkdir -p lib bin

libs: dirs $(LIBDIR)/ProdCons.xo $(LIBDIR)/Example.xo $(LIBDIR)/StackTest.xo $(LIBDIR)/Test.xo

$(LIBDIR)/%.xo: %.ob07
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

deps: dirs $(LIBDIR)/coroutines.o $(LIBDIR)/setjmp.o
	@cd rtl; ./build.sh
	@cp rtl/RTL_sys.xo $(LIBDIR)
	@cd $(LIBDIR); ar rcs libcoro.a RTL_sys.xo coroutines.o setjmp.o

$(LIBDIR)/%.o: %.asm
	$(FASM) $^ $@
	
Test: deps $(LIBDIR)/Test.xo
	$(LD) $(LDFLAGS) $(LIBDIR)/Test.xo $(LIBS) -o $(BINDIR)/Test
	
ProdCons: deps $(LIBDIR)/ProdCons.xo
	$(LD) $(LDFLAGS) $(LIBDIR)/ProdCons.xo $(LIBS) -o $(BINDIR)/ProdCons
	
Example: deps $(LIBDIR)/Example.xo
	$(LD) $(LDFLAGS) $(LIBDIR)/Example.xo $(LIBS) -o $(BINDIR)/Example

StackTest: deps $(LIBDIR)/StackTest.xo
	$(LD) $(LDFLAGS) $(LIBDIR)/StackTest.xo $(LIBS) -o $(BINDIR)/StackTest
	
Skynet: deps $(LIBDIR)/Skynet.xo
	$(LD) $(LDFLAGS) $(LIBDIR)/Skynet.xo $(LIBS) -o $(BINDIR)/Skynet

coro_example:
	$(CC) $(CFLAGS) -o $(BINDIR)/coro_example coro_example.c

clean:
	$(RM) $(BINDIR)/* $(LIBDIR)/*.o $(LIBDIR)/*.xo
	
