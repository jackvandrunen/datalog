OBJECTS = dlresolver.o dlstack.o
CCFLAGS = -std=c99 -Werror -Wall -Wextra -ggdb
CC = gcc

test: $(OBJECTS) test.c
	$(CC) $(CCFLAGS) $(OBJECTS) test.c -o test

dlresolver.o: dlresolver.h dlstack.h dlresolver.c
	$(CC) $(CCFLAGS) dlresolver.c -c

dlstack.o: dlstack.h dlstack.c
	$(CC) $(CCFLAGS) dlstack.c -c

clean:
	/bin/rm -f $(OBJECTS) test core.*
