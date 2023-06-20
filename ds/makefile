CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
GD = -g 
GC = -DNDEBUG -O3
CPPFLAGS = -I./
VLG = valgrind -s --leak-check=yes --track-origins=yes
GDB = cgdb

NAMESPACE = heap_q
LIBS = $(SRC)/dvector.c $(SRC)/heap.c

SRC = src
TEST = test
HEADER = include


TARGET = $(NAMESPACE).out
CFILE = $(SRC)/$(NAMESPACE).c $(TEST)/$(NAMESPACE)_test.c $(LIBS)

RELEASE_DIR = bin/release/$(NAMESPACE)_release.out
DEBUG_DIR = bin/debug/$(NAMESPACE)_debug.out

.PHONY: clean run_release run_debug vlg gdb release debug all

clean:
	@ rm  bin/release/*.out bin/debug/*.out
	
release:$(RELEASE_DIR)

run_debug:
	@ $(DEBUG_DIR)

gdb:
	@ $(GDB) $(DEBUG_DIR)

vlg:
	@ $(VLG) $(DEBUG_DIR)

$(RELEASE_DIR):$(CFILE)
	@ $(CC) $(CFLAGS) $(GC) $(CPPFLAGS)$(HEADER) -o $(RELEASE_DIR) $(CFILE)

debug: $(DEBUG_DIR)

$(DEBUG_DIR): $(CFILE)
	@ $(CC) $(CFLAGS) $(GD) $(CPPFLAGS)$(HEADER) -o $(DEBUG_DIR) $(CFILE) -lm
	
run_release:
	@ $(RELEASE_DIR) 
	
all:release debug

	
