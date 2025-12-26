CC = gcc
CFLAGS = -pthread
TARGET = producer_consumer

all: $(TARGET)

$(TARGET): producer_consumer.c
	$(CC) $(CFLAGS) producer_consumer.c -o $(TARGET)

start: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)