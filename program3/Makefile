CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o bit_flags.o

number_driver : $(OBJECTS)
	$(CC) $(CFLAGS) -o number_driver $(OBJECTS)
main.o : main.c 
	$(CC) $(CFLAGS) -c main.c -o main.o
bit_flags.o : status.h bit_flags.h bit_flags.c
	$(CC) $(CFLAGS) -c bit_flags.c -o bit_flags.o
clean:
	rm number_driver $(OBJECTS)
