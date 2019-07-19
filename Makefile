SDL_FLAGS:=$(shell pkg-config --cflags --libs sdl2)
CFLAGS+=-Wall -std=c11
INCLUDES=-Iinclude/ -I$(STB_HEADER_PATH)
LINKER_FLAGS=-lm
BUILDDIR=build/
CC=gcc

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:src/%.c=build/%.o)


.PHONY = all test clean format

all: test example/example

example/example: $(OBJS) example/main.c
		$(CC) $(CFLAGS) $(INCLUDES) $^ -o $(BUILDDIR)/example $(SDL_FLAGS) $(LINKER_FLAGS)

build/%.o: src/%.c
		@mkdir -p $(BUILDDIR)
		$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

clean:
			rm -rf $(BUILDDIR)

format:
			find -name *.[ch] | xargs clang-format -style=file -i


#
# Test infrastructure
#

TEST_SRCS=$(wildcard test/src/*.c)
TEST_OBJS=$(TEST_SRCS:test/src/%.c=build/test/%.o)
TEST_INCLUDES=$(INCLUDES) -Itest/include/

build/test/%.o: test/src/%.c
		@mkdir -p $(BUILDDIR)/test
		$(CC) $(CFLAGS) $(TEST_INCLUDES) -c $^ -o $@

_test: $(OBJS) $(TEST_OBJS)
		@mkdir -p $(BUILDDIR)/test
		$(CC) $(CFLAGS) $(TEST_INCLUDES) $^ -o $(BUILDDIR)/test/test $(LINKER_FLAGS) $(SDL_FLAGS)

test: _test
		@$(BUILDDIR)/test/test


