CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: programme
	./programme

programme: projet.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f programme

.PHONY: all clean

