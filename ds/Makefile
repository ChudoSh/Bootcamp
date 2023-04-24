CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
GD = -g
GC = -DNDEBUG -O3
CPPFLAGS = -I./

NAMESPACE = D_Vector
SRC = src
TEST= test
HEADER = include

TARGET = $(NAMESPACE).out
CFILE = $(SRC)/$(NAMESPACE).c $(TEST)/$(NAMESPACE)_Test.c

RELEASE_DIR = bin/release/$(NAMESPACE)_Release.out
DEBUG_DIR = bin/debug/$(NAMESPACE)_Debug.out

.PHONY: clean execute_release execute_debug release debug all

clean:
	rm $(RELEASE_DIR) $(DEBUG_DIR)
	
release:$(RELEASE_DIR)

execute_debug:
	$(DEBUG_DIR)

$(RELEASE_DIR):$(CFILE)
	$(CC) $(CFLAGS) $(GC) $(CPPFLAGS)$(HEADER) -o $(RELEASE_DIR) $(CFILE)

debug: $(DEBUG_DIR)

$(DEBUG_DIR): $(CFILE)
	$(CC) $(CFLAGS) $(GD) $(CPPFLAGS)$(HEADER) -o $(DEBUG_DIR) $(CFILE)
	
execute_release:
	$(RELEASE_DIR) 
	
all:release debug

	
