CC = gcc
CFLAGS = -Wall -g
OBJS = main.o file_operations.o directory_ops.o permissions.o logger.o utils.o
TARGET = file_manager

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o bin/$(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) bin/$(TARGET)
