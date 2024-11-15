CC=cc
LIBS=./lib/libraylib-i686.a
INCLUDE=./include
CFLAGS=-m32 -no-pie
OBC=../../../compilerX
DEF=-def API_sys
OPTS=-entry _start -rtl RTL_sys
SRCO=Snowflake.ob07
OBJC=lib/raylib_glue.o
OBJO=lib/Snowflake.xo
EXE=bin/Snowflake

exe: $(OBJC) $(OBJO)
	@mkdir -p bin
	$(CC) $(CFLAGS) -nostartfiles -o $(EXE) $^ $(LIBS) -lm

lib/%.o: lib/%.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(INCLUDE)

lib/Snowflake.xo: $(SRCO)
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

clean:
	$(RM) $(EXE) $(OBJC) $(OBJO)
