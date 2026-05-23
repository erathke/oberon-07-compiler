CC=cc
AR=ar
LIBS=./lib/libraylib-i686.a ./lib/libmurl.a
INCLUDE=./include
CFLAGS=-m32 -no-pie
ARFLAGS=rc
OBC=../../../compilerX
DEF=-def API_sys
OPTS=-entry _start -rtl RTL_sys
OBJC=lib/raylib_glue.o lib/glue.o
OBJO=lib/HelloGUI.xo
BINDIR=bin
EXE=$(BINDIR)/HelloGUI
MURL_DEP=./deps/microui-raylib
MURL_SRC=$(MURL_DEP)/src/murl.c $(MURL_DEP)/vendor/microui.c

all: deps exe

exe: $(OBJC) $(OBJO)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -nostartfiles -o $(EXE) $^ $(LIBS) -lm

lib/%.o: lib/%.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE)

lib/%.xo: %.ob07
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

clean:
	$(RM) $(EXE) $(OBJC) $(OBJO)
	
deps: $(MURL_SRC)
	$(CC) $(CFLAGS) -c $(MURL_DEP)/src/murl.c -o lib/murl.o -I$(MURL_DEP)/vendor -I./include
#	$(CC) $(CFLAGS) -c $(MURL_DEP)/vendor/microui.c -o lib/microui.o
	$(AR) $(ARFLAGS) lib/libmurl.a lib/murl.o lib/microui.o
