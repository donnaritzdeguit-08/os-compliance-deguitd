CC = gcc
CFLAGS = -pthread
TARGET = dining-philosophers

all: $(TARGET)

$(TARGET): dining-philosophers.c
	$(CC) $(CFLAGS) dining-philosophers.c -o $(TARGET)

start: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)