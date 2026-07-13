CC = mpicc 
CFLAGS = -Wall -Wextra -O2 -fopenmp -Iinclude 
LDFLAGS = -fopenmp -lm

SRC = src/main.c src/utils/io.c src/utils/sequences.c src/algorithm/algorithm.c src/algorithm/primitives/list.c src/hpc/mpi_handler.c

OBJDIR = build
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

TARGET = build/smith_waterman

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p build
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJDIR) $(TARGET)