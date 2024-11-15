CC=cc
LIBS=./lib/libraylib-i686.a
INCLUDE=./include
CFLAGS=-m32 -no-pie
OBC=../../../compilerX
DEF=-def API_sys
OPTS=-entry _start -rtl RTL_sys
SRCO=HelloGui.ob07
OBJC=lib/raylib_glue.o lib/glue.o
OBJO=lib/HelloGui.xo
EXE=bin/HelloGui

exe: $(OBJC) $(OBJO)
	@mkdir -p bin
	$(CC) $(CFLAGS) -nostartfiles -o $(EXE) $^ $(LIBS) -lm

lib/%.o: lib/%.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE)

lib/HelloGui.xo: $(SRCO)
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

clean:
	$(RM) $(EXE) $(OBJC) $(OBJO)
