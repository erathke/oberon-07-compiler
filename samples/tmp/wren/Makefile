CC=cc
LIBS=./lib/libraylib-i686.a ./lib/libwren-i686.a
INCLUDE=./include
CFLAGS=-m32 -no-pie -nostartfiles
OBC=../../../compilerX
DEF=-def API_sys
OPTS=-entry _start -rtl RTL_sys
SRCC=lib/glue.c
SRCO=AmigaBall.ob07
OBJC=lib/glue.o
OBJO=lib/AmigaBall.xo
BINDIR=bin
EXE=$(BINDIR)/AmigaBall

amiga: $(OBJC) $(OBJO)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(EXE) $^ $(LIBS) -lm

lib/glue.o: $(SRCC)
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE)

lib/%.xo: %.ob07
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

wren: lib/HelloWren.xo
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/HelloWren $^ ./lib/libwren-i686.a -lm
	
arena: lib/TestArena.xo
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/TestArena $^ ./lib/libwren-i686.a -lm

clean:
	$(RM) $(BINDIR)/* lib/*.xo
