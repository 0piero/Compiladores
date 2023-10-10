CC = gcc
TARGET = main
SRC = $(wildcard */*.c)
OBJ = $(SRC:.c=.o)
SRC_MAIN = $(wildcard *.c)
MAIN = $(SRC_MAIN:.c=.o)
CFLAGS = -Wall

all: $(OBJ) $(MAIN)
	$(MAKE) -C utils
	$(CC) -o $(TARGET) $(OBJ) $(MAIN) $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm *.o
	rm main
	rm main.exe