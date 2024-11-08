CC=cc
LIBS=./lib/libraylib-i686.a ./lib/libwren-i686.a
INCLUDE=./include
CFLAGS=-m32 -no-pie -nostartfiles
OBC=../../../compilerX
DEF=-def API_sys
OPTS=-entry _start -rtl RTL_sys
SRCC=lib/glue.c
SRCO=HelloGui.ob07
OBJC=lib/glue.o
OBJO=lib/HelloGui.xo
BINDIR=bin
EXE=$(BINDIR)/HelloGui

exe: $(OBJC) $(OBJO)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(EXE) $^ $(LIBS) -lm

lib/glue.o: $(SRCC)
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE)

lib/%.xo: %.ob07
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

#lib/HelloWren.xo: HelloWren.ob07
#	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

wren: lib/HelloWren.xo
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/HelloWren $^ ./lib/libwren-i686.a -lm
	
arena: lib/TestArena.xo
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/TestArena $^ ./lib/libwren-i686.a -lm

clean:
	$(RM) $(EXE) $(OBJC) $(OBJO)

wipe:
	$(RM) $(BINDIR)/* lib/*.xo
