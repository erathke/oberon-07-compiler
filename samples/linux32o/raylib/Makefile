CC=cc
MACHINE?=`uname -m`
LIBS=./lib/libraylib-$(MACHINE).a
INCLUDE=./include
CFLAGS=-m32 -no-pie
OBC=../../../compilerX
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
	$(OBC) $^ linux32o -out $@

clean:
	$(RM) $(EXE) $(OBJC) $(OBJO)
