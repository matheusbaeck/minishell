CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = run
SRC = run.c

all: $(TARGET)
	rm -rf files
	./run Generating

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)