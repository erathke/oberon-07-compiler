CC=cc
MACHINE?=`uname -m`
LIBS=./lib/libraylib-$(MACHINE).a ./lib/libmurl.a
INCLUDE=./include
CFLAGS=-m32 -no-pie
OBC=../../../compilerX
SRCC=lib/glue.c
SRCO=HelloGui.ob07
OBJC=lib/glue.o
OBJO=lib/HelloGui.xo
EXE=HelloGui
MURL_DEP=./deps/microui-raylib
MURL_SRC=$(MURL_DEP)/src/murl.c $(MURL_DEP)/vendor/microui.c

exe: $(OBJC) $(OBJO)
	$(CC) $(CFLAGS) -nostartfiles -o $(EXE) $^ $(LIBS) -lm

lib/glue.o: $(SRCC)
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE)

lib/HelloGui.xo: $(SRCO)
	$(OBC) $^ linux32o -out $@

clean:
	$(RM) $(EXE) $(OBJC) $(OBJO)
	
deps: $(MURL_SRC)
	$(CC) $(CFLAGS) -c $(MURL_DEP)/src/murl.c -o lib/murl.o -I$(MURL_DEP)/vendor -I./include
	$(CC) $(CFLAGS) -c $(MURL_DEP)/vendor/microui.c -o lib/microui.o
	ar rc lib/libmurl.a lib/murl.o lib/microui.o
