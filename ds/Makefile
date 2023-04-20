CC = gcc

CFLAGS = -ansi -pedantic-errors -Wall -Wextra

GD = -g

GC = -DNDEBUG -O3

NAMESPACE = Stack
INCLUDE = -I./include
TARGET = $(NAMESPACE).out
OBJ = src/$(NAMESPACE).c test/$(NAMESPACE)_Test.c

RELEASE_DIR = bin/release/$(NAMESPACE)_Release.out
DEBUG_DIR = bin/debug/$(NAMESPACE)_Debug.out

: $(OBJ) 
	$(CC) $(CFLAGS) $(GD) $(INCLUDE) -o $(TARGET) $(OBJ)

.PHONY: cleanobj cleanouts foo.c release debug all

cleanobj:
	rm $(wildcard *.o)
	
cleanouts:
	rm $(wildcard *.out)
	
release: $(RELEASE_DIR)

foo.c:$(TARGET)

$(RELEASE_DIR): $(OBJ)
	$(CC) $(CFLAGS) $(GC) $(INCLUDE) -o $(RELEASE_DIR) $(OBJ)

debug: $(DEBUG_DIR)

$(DEBUG_DIR): $(OBJ)
	$(CC) $(CFLAGS) $(GD) $(INCLUDE) -o $(DEBUG_DIR) $(OBJ)
	
all:$(RELEASE_DIR) $(DEBUG_DIR)

	
