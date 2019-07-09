SDL_FLAGS:=$(shell pkg-config --cflags --libs sdl2)
CFLAGS+=-Wall -std=c11
INCLUDES=-Iinclude/
BUILDDIR=build/
CC=gcc

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:src/%.c=build/%.o)

.PHONY = all clean format

all: example

example: $(OBJS) example/main.c
		$(CC) $(CFLAGS) $(INCLUDES) $^ -o $(BUILDDIR)/example $(SDL_FLAGS)

build/%.o: src/*.c
		@mkdir -p $(BUILDDIR)
		$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

clean:
			rm -rf $(BUILDDIR)

format:
			find -name *.[ch] | xargs clang-format -style=file -i
