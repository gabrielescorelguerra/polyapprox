CC = gcc
CFLAGS = -Wall -Wextra

OBJ_DIR = build

OBJ = $(OBJ_DIR)/polyapprox.o $(OBJ_DIR)/avl.o $(OBJ_DIR)/minheap.o
HEADERS = polyapprox.h avl.h minheap.h
SRC = polyapprox.c avl.c minheap.c

all: polyapprox

polyapprox: main.c $(OBJ)
	$(CC) $(CFLAGS) -o polyapprox main.c $(OBJ)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
