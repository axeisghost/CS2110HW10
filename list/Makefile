CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror -Wextra
RELEASE_FLAGS = -O2
DEBUG_FLAGS = -g -DDEBUG

run-test : build-release
	./test

run-debug : build-debug
	./test

run-gdb : build-debug
	gdb ./test

run-valgrind : build-debug
	valgrind --leak-check=yes --show-reachable=yes --tool=memcheck ./test

build-release : CFLAGS += $(RELEASE_FLAGS)
build-release : list.o test.o list.h
	$(CC) $(CFLAGS) test.o list.o -o test

build-debug : CFLAGS += $(DEBUG_FLAGS)
build-debug : list.o test.o list.h
	$(CC) $(CFLAGS) test.o list.o -o test

list.o : list.c list.h
	$(CC) $(CFLAGS) -c list.c

test.o : test.c list.h
	$(CC) $(CFLAGS) -c test.c

clean :
	rm *.o test
