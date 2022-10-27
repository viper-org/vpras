SHELL=/bin/sh

PREFIX=.
EXEC_PREFIX=$(PREFIX)

INCLUDEDIR=$(EXEC_PREFIX)/include
LIBDIR=$(EXEC_PREFIX)/lib
SRCDIR=$(EXEC_PREFIX)/src
TESTDIR=$(EXEC_PREFIX)/tests

PLATFORM_CXXFLAGS=
PLATFORM_LDFLAGS=

ifneq ($(OS),Windows_NT)
	PLATFORM_CXXFLAGS= -fsanitize=address,undefined 
	PLATFORM_LDFLAGS= -fsanitize=address,undefined 
endif

CXXC=g++
LD=g++

CXX_FLAGS=$(PLATFORM_CXXFLAGS) -O0 -ggdb3 -I$(INCLUDEDIR) -std=c++17 -Wall -Wextra -Wpedantic
LD_FLAGS=$(PLATFORM_LDFLAGS)

CXX_SRCS:=$(shell find $(SRCDIR) -name '*.cc')
OBJS:=${CXX_SRCS:.cc=.o}

TARGET=vpras

.PHONY: all clean

all: $(TARGET)

%.o: %.cc
	$(CXXC) $(CXX_FLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(LD) $(LD_FLAGS) $^ -o $@

clean:
	rm -rf $(TARGET) $(OBJS)