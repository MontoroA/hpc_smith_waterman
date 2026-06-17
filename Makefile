CC = gcc
CFLAGS = -Wall -Wextra -O2 -fopenmp

# Source files
SRC = main.c utils.c algorithm.c list.c
OBJ = $(SRC:.c=.o)

# Executable name
TARGET = smith_waterman

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)