CFLAGS = -std=c99 -Wall -Wextra
COMMON_SOURCES = src/murl.c vendor/microui.c
EXAMPLES = $(wildcard examples/*.c)

.PHONY: all
all: $(basename $(EXAMPLES))

examples/%: examples/%.c $(COMMON_SOURCES)
	cc $(CFLAGS) -o $@ $^ -I./include -I./vendor -I./src ./lib/libraylib-`uname -m`.a -lm

lib:
	cc -m32 -no-pie -c src/murl.c -I./vendor -I../../include -o lib/murl.o
	cc -m32 -no-pie -c vendor/microui.c -I./vendor -o lib/microui.o
	ar rc lib/libmurl.a lib/murl.o lib/microui.o
