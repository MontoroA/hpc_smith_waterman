CC = mpicc 
CFLAGS = -Wall -Wextra -O2 -fopenmp -Iinclude 
LDFLAGS = -fopenmp -lm

MAIN_SRC = src/main.c
UTILS_SRC = src/utils/io.c src/utils/sequences.c src/utils/reports.c
ALGORITHM_SRC = src/algorithm/algorithm.c src/algorithm/blocks.c src/algorithm/master.c src/algorithm/slave.c
PRIMITIVES_SRC = src/algorithm/primitives/list.c src/algorithm/primitives/queue.c
HPC_SRC = src/hpc/mpi_handler.c

SRC = $(MAIN_SRC) $(UTILS_SRC) $(ALGORITHM_SRC) $(PRIMITIVES_SRC) $(HPC_SRC)

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