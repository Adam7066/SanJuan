CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
.PHONY: all clean

all:
	$(CC) initGame.c cJSON.c -o initGame $(CFLAGS)
	$(CC) game.c cJSON.c -o game $(CFLAGS)

clean:
	$(RM) initGame game