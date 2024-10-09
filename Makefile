CC=gcc
CFLAGS=-Wall

build: main

main: tema1.o lists.o queue.o
	$(CC) $(CFLAGS) tema1.o lists.o queue.o -o tema1

tema1.o: tema1.c lists.h queue.h 
	$(CC) $(CFLAGS) -c tema1.c -o tema1.o

lists.o: lists.c lists.h 
	$(CC) $(CFLAGS) -c lists.c -o lists.o

queue.o: queue.c queue.h 
	$(CC) $(CFLAGS) -c queue.c -o queue.o

run:
	./tema1

clean:
	rm -f tema1 *.o
