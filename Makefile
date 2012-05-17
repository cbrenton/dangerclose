# Original SDL-GL-basic Makefile template written by Hans de Ruiter
# Modified by Chris Brenton
#
# License:
# This source code can be used and/or modified without restrictions.
# It is provided as is and the author disclaims all warranties, expressed 
# or implied, including, without limitation, the warranties of
# merchantability and of fitness for any purpose. The user must assume the
# entire risk of using the Software.

CC     = g++
GPU_CC = nvcc
CP     = cp
RM     = rm -rf
KILL   = killall -9
SHELL  = /bin/sh
MAKE   = make

IFLAGS = -I./src -I./lib
LFLAGS =
DEBUG = -ggdb
OPTIMIZE = -O3
ERROR = -Werror
CFLAGS = $(OPTIMIZE) -Wall -c $(DEBUG) $(ERROR) $(IFLAGS)
LDFLAGS = $(OPTIMIZE) $(DEBUG) $(ERROR) $(LFLAGS)

TARGET = dangerzone
INPUTEXT=pov
INPUTDIR=input
INPUTFILE=test
OUTPUTDIR=images
OUTPUTEXT=tga
WIDTH=640
HEIGHT=640
ARGS = -w $(WIDTH) -h $(HEIGHT) -i $(INPUTDIR)/$(INPUTFILE).$(INPUTEXT)

# Additional linker libraries
LIBS = $(LIBFLAGS)

# -------------------------------------------------------------
# Nothing should need changing below this line

# The source files
SRCS = $(wildcard src/*.cpp src/*/*.cpp)

OBJS = $(SRCS:.cpp=.o)

# Rules for building
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: lib
lib:
	$(shell) ./lib.sh

run:
	./$(TARGET) $(ARGS)

eog:
	eog ./$(OUTPUTDIR)/$(INPUTFILE).$(OUTPUTEXT)

test:	run eog

gdb:
	gdb --args ./$(TARGET) $(ARGS)

vg:	valgrind

valgrind:
	valgrind --tool=memcheck --leak-check=full ./$(TARGET) $(ARGS)

clean:
	$(RM) $(TARGET) $(OBJS)

killall:
	$(KILL) $(TARGET)
