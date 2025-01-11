CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: main

main: voiture.o session.o main.o
	$(CC) $(CFLAGS) -o main voiture.o session.o main.o

main.o: src/main.c src/voiture.h src/session.h
	$(CC) $(CFLAGS) -c src/main.c

voiture.o: src/voiture.c src/voiture.h
	$(CC) $(CFLAGS) -c src/voiture.c

session.o: src/session.c src/session.h
	$(CC) $(CFLAGS) -c src/session.c

clean:
	rm -f *.o main
