TARGETNAME = $(shell basename -a $(wildcard ./src/*.c))
TESTNAME = $(basename $(TARGETNAME) .c)

CC       = gcc
CFLAGS   = -ansi -pedantic-errors -Wall -Wextra -g -I $(IDIR)
RLSFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I $(IDIR)

LDFLAGS   = -L -Wl,rpath=$(DBG_LDLIB)
REL_LDLIB = $(RELDIR)/rel_libds.so
DBG_LDLIB = $(DBGDIR)/dbg_libds.so

VLG = valgrind -s --leak-check=yes --track-origins=yes
GDB = cgdb

NAMESPACE = signal_ping_pong
RELEASE_DIR = bin/release/$(NAMESPACE)_release.out
DEBUG_DIR = bin/debug/$(NAMESPACE)_test_dbg.out

IDIR    = include
SDIR    = src
TESTDIR = test
BINDIR  = bin
RELDIR  = bin/release
DBGDIR  = bin/debug

TESTS 	 := $(wildcard test/*.c)
SRCS     := $(wildcard src/*.c)
TEST_OBJ := $(subst $(TESTDIR), $(BINDIR), $(TESTS:_test.c=_test.o))
TEST_OUT := $(TEST_OBJ:_test.o=_test.out)
REL_OBJS := $(subst $(SDIR), $(BINDIR), $(SRCS:.c=_r.o))
DBG_OBJS := $(subst $(SDIR), $(BINDIR), $(SRCS:.c=_d.o))
HDRS     := $(wildcard include/*.h)
DEPS      = $(LDLIBS) $(BINDIR)/%_test.o

%_test: $(DEPS)
	$(CC) $(CFLAGS) $(BINDIR)/$@.o $(LDFLAGS) $(DBG_LDLIB) -o $@.out

$(BINDIR)/%_r.o: $(SDIR)/%.c
	$(CC) $(RLSFLAGS) -c -fPIC -o $@ $?
	
$(BINDIR)/%_d.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $? 
	
.PRECIOUS: $(BINDIR)/$(wildcard *.so) 

.PHONY: debug release test clean all run gdb vlg

all: release debug

debug: $(DBG_OBJS)
	@ $(CC) $(CFLAGS) -shared -o $(DBG_LDLIB) $?
	
release: $(REL_OBJS)
	@ $(CC) $(RLSFLAGS) -shared -o $(REL_LDLIB) $?
	
test : debug  
	@ $(foreach d, $(TESTNAME), $(CC) $(CFLAGS) ./test/$d_test.c -o \
	./bin/debug/$d_test_dbg.out $(LDFLAGS) $(DBG_LDLIB);)
	
clean: 
	@ rm -f $(REL_OBJS) $(DBG_OBJS) $(wildcard *.out)

run:
	@ $(DEBUG_DIR)

gdb:
	@ $(GDB) $(DEBUG_DIR)

vlg:
	@ $(VLG) $(DEBUG_DIR)



