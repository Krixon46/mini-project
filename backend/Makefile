CC = gcc
CFLAGS = -Wall -Wextra -pthread -O2 -D_GNU_SOURCE
LDFLAGS = -pthread
TARGET = http_server

SRC = src/http_server.c src/csv.c src/array_ops.c src/sort.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o build/$(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o build/$(TARGET)

run: $(TARGET)
	./build/$(TARGET)

.PHONY: all clean run
