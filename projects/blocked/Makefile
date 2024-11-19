CC=cc
LIBS=./lib/libraylib-i686.a ./lib/libmurl.a
INCLUDE=./include
CFLAGS=-m32 -no-pie
OBC=../../compilerX
DEF=-def API_sys
OPTS=-entry _start -rtl RTL_sys
SRCO=BlockEditor.ob07
OBJC=lib/raylib_glue.o lib/microui_glue.o
OBJO=lib/BlockEditor.xo
EXE=bin/BlockEditor
FS_FILE=disk0.raw
FS_BLOCKS?=10
FS_BLOCK_SIZE?=4096

exe: $(OBJC) $(OBJO)
	@mkdir -p bin
	$(CC) $(CFLAGS) -nostartfiles -o $(EXE) $^ $(LIBS) -lm

lib/%.o: lib/%.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE)

lib/%.xo: %.ob07
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

hello: lib/Hello.xo

fs:
	dd if=/dev/zero of=$(FS_FILE) count=$(FS_BLOCKS) bs=$(FS_BLOCK_SIZE)

clean:
	$(RM) bin/* $(OBJC) $(OBJO)
