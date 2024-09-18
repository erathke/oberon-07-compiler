CC=cc
MACHINE?=`uname -m`
LIBS=./lib/libraylib-$(MACHINE).a ./lib/libmurl.a
INCLUDE=./include
CFLAGS=-m32 -no-pie
OBC=../../../compilerX
SRCC=lib/glue.c
SRCO=HelloGui.ob07
OBJC=glue.o
OBJO=HelloGui.xo
EXE=HelloGui

exe: $(OBJC) $(OBJO)
	$(CC) $(CFLAGS) -o $(EXE) $^ $(LIBS) -lm

glue.o: $(SRCC)
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE)

HelloGui.xo: $(SRCO)
	$(OBC) $^ linux32o -out $@

clean:
	$(RM) $(EXE) $(OBJC) $(OBJO)
