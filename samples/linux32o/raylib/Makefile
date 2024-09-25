CC=cc
LIBS=./lib/libraylib-i686.a
INCLUDE=./include
CFLAGS=-m32 -no-pie
OBC=../../../compilerX
DEF=-def API_sys
OPTS=-entry _start -rtl RTL_sys
SRCC=lib/glue.c
SRCO=HelloGui.ob07
OBJC=lib/glue.o
OBJO=lib/HelloGui.xo
EXE=HelloGui

exe: $(OBJC) $(OBJO)
	$(CC) $(CFLAGS) -nostartfiles -o $(EXE) $^ $(LIBS) -lm

lib/glue.o: $(SRCC)
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE)

lib/HelloGui.xo: $(SRCO)
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

clean:
	$(RM) $(EXE) $(OBJC) $(OBJO)
