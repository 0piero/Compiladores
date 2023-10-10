CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall

all: $(OBJ)
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
