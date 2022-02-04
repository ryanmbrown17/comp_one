CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o stack.o

stack__driver : $(OBJECTS)
	$(CC) $(CFLAGS) -o stack_driver $(OBJECTS)
main.o : main.c 
	$(CC) $(CFLAGS) -c main.c -o main.o
stack.o : status.h stack.h stack.c 
	$(CC) $(CFLAGS) -c stack.c -o stack.o
clean:
	rm stack_driver $(OBJECTS)
