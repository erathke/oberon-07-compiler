CC=cc
LIBS=-lX11 -ldockapp
INCLUDE=./include
CFLAGS=-m32 -no-pie
OBC=../../../compilerX
DEF=-def API_sys
OPTS=-entry _start -rtl RTL_sys
SRCC=lib/glue.c
SRCO=HelloDA.ob07
OBJC=lib/glue.o
OBJO=lib/HelloDA.xo
EXE=bin/wmbacklight

exe: $(OBJC) $(OBJO)
	@mkdir -p bin
	$(CC) $(CFLAGS) -nostartfiles -o $(EXE) $^ $(LIBS) -lm

lib/glue.o: $(SRCC)
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE)

lib/HelloDA.xo: $(SRCO)
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

clean:
	$(RM) $(EXE) $(OBJC) $(OBJO)
