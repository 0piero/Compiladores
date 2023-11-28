CC = gcc
TARGET = parse
SRC = $(wildcard */*.c)
OBJ = $(SRC:.c=.o)
SRC_MAIN = $(wildcard *.tab.c)
MAIN = $(SRC_MAIN:.c=.o)
CFLAGS = -Wall

all: $(OBJ) $(MAIN)
	$(CC) -o $(TARGET) $(OBJ) $(MAIN) $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm */*.o
	rm *.o
	rm parse