CC = gcc
TARGET = main
SRC = $(wildcard */*.c)
OBJ = $(SRC:.c=.o)

SRC_OUT = $(wildcard *.tab.c)
OBJ_OUT = $(SRC_OUT:.c=.o)

CFLAGS = -Wall

all: $(OBJ) $(OBJ_OUT) $(MAIN)
	$(CC) -o $(TARGET) $(OBJ) $(OBJ_OUT) main.c $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm */*.o
	rm *.o
	rm main