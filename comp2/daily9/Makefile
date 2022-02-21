CC = gcc 
CFLAGS = -Wall --std=c99
OBJECTS = main.o priority_queue.o

driver: $(OBJECTS)
	$(CC)$(CFLAGS) -o driver $(OBJECTS)
main.o:main.c
	$(CC)$(CFLAGS) -o main.o -c main.c
priority_queue.o:priority_queue.h priority_queue.c
	$(CC)$(CFLAGS) -o priority_queue.o -c priority_queue.c

clean:
	rm driver $(OBJECTS)
