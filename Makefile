CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = src
OBJ = obj

OBJS = $(OBJ)/voiture.o $(OBJ)/session.o $(OBJ)/essais.o $(OBJ)/qualifications.o $(OBJ)/course.o $(OBJ)/main.o
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o $(OBJ)/main.o

$(OBJ)/voiture.o: $(SRC)/voiture.c
	$(CC) $(CFLAGS) -c $(SRC)/voiture.c -o $(OBJ)/voiture.o

$(OBJ)/session.o: $(SRC)/session.c
	$(CC) $(CFLAGS) -c $(SRC)/session.c -o $(OBJ)/session.o

$(OBJ)/essais.o: $(SRC)/essais.c
	$(CC) $(CFLAGS) -c $(SRC)/essais.c -o $(OBJ)/essais.o

$(OBJ)/qualifications.o: $(SRC)/qualifications.c
	$(CC) $(CFLAGS) -c $(SRC)/qualifications.c -o $(OBJ)/qualifications.o

$(OBJ)/course.o: $(SRC)/course.c
	$(CC) $(CFLAGS) -c $(SRC)/course.c -o $(OBJ)/course.o

clean:
	rm -f $(OBJ)/*.o $(EXEC)
