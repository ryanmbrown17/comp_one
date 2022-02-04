CC = gcc
CLFAGS = -g -Wall --std=c99 
OBJECTS = my_string.o  main.o generic_vector.o

main_test: my_string.o generic_vector.o main.o tree.o
	$(CC)$(CFLAGS) -o main_test main.o tree.o my_string.o generic_vector.o
main.o: main.c
	$(CC)$(CFLAGS) -c main.c -o main.o
tree.o: tree.c
	$(CC)$(CFLAGS) -c tree.c -o tree.o
generic_vector.o: generic_vector.c
	$(CC)$(CFLAGS) -c generic_vector.c -o generic_vector.o
my_string.o:my_string.c
	$(CC)$(CFLAGS) -c my_string.c -o my_string.o

clean:
	rm main_test $(OBJECTS)
