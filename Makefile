# Makefile for BitBoard Checkers

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Source files and object files
SRCS = main.c game.c bitboard.c
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = checkers

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean