CC=gcc
CFLAGS=-lpthread
LDFLAGS=-c -Wall

all: main.o utils.o rs232.o commandthread.o
	$(CC) $(LDFLAGS) utils.o rs232.o commandthread.o main.o -o scmd

main.o: main.c
	$(CC) $(CFLAGS) main.c

utils.o: utils.c
	$(CC) $(CFLAGS) utils.c

rs232.o: rs232.c
	$(CC) $(CFLAGS) rs232.c

commandthread.o: commandthread.c
	$(CC) $(CFLAGS) commandthread.c

clean:
	rm -rf *.o scmd
