# Install
BIN = demo

# Flags
#CFLAGS += -std=c89 -pedantic -O0
CFLAGS += -std=c89 -no-pie
CFLAGS += -I/usr/include/SDL2

SRC = main.c
OBJ = $(SRC:.c=.o)
LIBS += -lm -lSDL2

$(BIN):
	@mkdir -p bin
	rm -f bin/$(BIN) $(OBJS)
	$(CC) $(SRC) $(CFLAGS) -o bin/$(BIN) demo.xo $(LIBS)
