#include "../algorithm/blocks.h"
#include "../utils/reports.h"
#include <stdio.h>

#define CHECKPOINT_FILE_PATH "./data/temp/checkpoint.bin"
#define CHECKPOINT_INTERVAL 2
#define MAX_CHECKPOINT_SIZE (1000 * 80000) + sizeof(CheckpointHeader) // 8KB por MatrixBlock si BLOCK_SIZE = 10000, como maximo entonces el checkpoint puede ocupar 800MB

typedef struct
{
    uint32_t last_wavefront_computed;
    double accumulated_time;
} CheckpointHeader;

FILE *create_checkpoint_file(const char *filename, double start_time);

FILE *open_checkpoint_file(const char *filename);

int load_from_checkpoint(FILE *file, BlockMap *map, double last_time, double *accumulated_time);

void auto_save_checkpoint(uint32_t *next_wavefront_number, FILE *fp, BlockMap *map);