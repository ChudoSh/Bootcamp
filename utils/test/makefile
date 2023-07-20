
all: lib_wd.so watchdog_test.out watchdog_prg.out

WD_LIB_SRC = watchdog.c ../../ds/src/scheduler_heap.c ../../ds/src/heap_q.c ../../ds/src/uid.c ../../ds/src/task.c ../../ds/src/heap.c ../../ds/src/dvector.c

lib_wd.so: $(WD_LIB_SRC)
	gcc -ansi -pedantic-errors -Wall -g  -I ../include -I ../../ds/include -fPIC -shared $(WD_LIB_SRC) -o lib_wd.so -lpthread

watchdog_prg.out: watchdog_prg.c
	gcc -ansi -pedantic-errors -Wall -g -I ../include -I ../../ds/include watchdog_prg.c -o watchdog_prg.out -L. -l_wd -Wl,-rpath=.

watchdog_test.out: watchdog_test.c
	gcc -ansi -pedantic-errors -Wall -g -I ../include -I ../../ds/include watchdog_test.c -o watchdog_test.out -L. -l_wd -Wl,-rpath=.
clean:
	rm -f lib_wd.so watchdog_prg.out watchdog_test.out
