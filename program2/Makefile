CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o queue.o

queue_driver : $(OBJECTS)
	$(CC) $(CFLAGS) -o queue_driver $(OBJECTS)
main.o : main.c 
	$(CC) $(CFLAGS) -c main.c -o main.o
queue.o : status.h queue.h queue.c
	$(CC) $(CFLAGS) -c queue.c -o queue.o
clean:
	rm queue_driver $(OBJECTS)
