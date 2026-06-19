CC = gcc
CFLAGS = -Wall -Wextra

OBJ_DIR = build

OBJ = polyapprox.o
HEADERS = polyapprox.h
SRC = polyapprox.c

all: polyapprox

polyapprox: main.c $(OBJ_DIR)/$(OBJ)
	$(CC) $(CFLAGS) -o polyapprox main.c $(OBJ_DIR)/$(OBJ)

$(OBJ_DIR)/$(OBJ): $(HEADERS) $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ_DIR)/$(OBJ)