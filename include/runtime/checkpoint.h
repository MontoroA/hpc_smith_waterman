#include "../algorithm/blocks.h"
#include "../utils/reports.h"
#include <stdio.h>

#define CHECKPOINT_FILE_PATH "./data/temp/checkpoint.bin"
#define CHECKPOINT_INTERVAL 2

typedef struct
{
    int last_wavefront_computed;

} CheckpointHeader;

FILE *create_checkpoint_file(const char *filename);

FILE *open_checkpoint_file(const char *filename);

int save_wavefront_to_checkpoint(FILE *file, int wavefront_number, BlockMap *map);

int load_from_checkpoint(FILE *file, BlockMap *map);

void auto_save_checkpoint(int *next_wavefront_number, FILE *fp, BlockMap *map);