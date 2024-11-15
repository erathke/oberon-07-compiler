CC=cc
LIB_WREN=./lib/libwren-i686.a
LIB_RAYLIB=./lib/libraylib-i686.a
LIBS=$(LIB_WREN) $(LIB_RAYLIB)
INCLUDE=./include
CFLAGS=-m32 -no-pie -nostartfiles
OBC=../../../compilerX
DEF=-def API_sys
OPTS=-entry _start -rtl RTL_sys
BINDIR=bin

all: amiga arena skynet

lib/%.o: lib/%.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE)

lib/%.xo: %.ob07
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

amiga: lib/raylib_glue.o lib/AmigaBall.xo
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ $(LIBS) -lm

arena: lib/TestArena.xo
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ $(LIB_WREN) -lm

skynet: lib/Skynet.xo
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ $(LIB_WREN) -lm

clean:
	$(RM) $(BINDIR)/* lib/*.xo lib/*.o
