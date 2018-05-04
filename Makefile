OBJECTS = dlresolver.o dlstack.o dltoken.o dlparser.o
CCFLAGS = -std=c99 -Werror -Wall -Wextra -ggdb
CC = gcc

test: dlresolver.o dlstack.o test.c
	$(CC) $(CCFLAGS) dlresolver.o dlstack.o test.c -o test

test2: dltoken.o dlparser.o test2.c
	$(CC) $(CCFLAGS) dltoken.o dlparser.o test2.c -o test2

dlresolver.o: dlresolver.h dlstack.h dlresolver.c
	$(CC) $(CCFLAGS) dlresolver.c -c

dlstack.o: dlstack.h dlstack.c
	$(CC) $(CCFLAGS) dlstack.c -c

dltoken.o: dltoken.h dltoken.c
	$(CC) $(CCFLAGS) dltoken.c -c

dlparser.o: dltoken.h dlparser.h dlparser.c
	$(CC) $(CCFLAGS) dlparser.c -c

clean:
	/bin/rm -f $(OBJECTS) test test2 core.*
