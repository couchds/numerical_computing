CC=gcc
CFLAGS=-c

all: numerical_computing

numerical_computing: main.o interface.o computation.o
	mpicc main.o interface.o computation.o -o NC

computation.o: computation.c
	$(CC) $(CFLAGS) computation.c -o computation.o

interface.o: interface.c
	$(CC) $(CFLAGS) interface.c -o interface.o

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

clean:
	rm *.o *.out NC
