CC=gcc
CFLAGS=-Wall -Wextra -g -Iinclude

SRC=$(wildcard src/core/*.c src/commands/*.c src/utils/*.c)
OBJ=$(SRC:.c=.o)

BIN=eafitos

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(BIN)

run: all
	./$(BIN)
