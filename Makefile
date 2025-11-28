# Compiler and flags
CC = gcc
CFLAGS = -Wall -pthread

# Source files
SRCS = src/main.c src/buffer.c src/prod.c src/cons.c src/sync.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = prodcons

# Default target
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
