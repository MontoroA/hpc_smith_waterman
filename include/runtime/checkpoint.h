#include "blocks.h"
#include <stdio.h>

typedef struct
{
    int last_wavefront_computed;

} CheckpointHeader;

FILE *create_checkpoint_file(const char *filename);

void save_wavefront_to_checkpoint(FILE *file, int wavefront_number, BlockMap *map);

void load_from_checkpoint(FILE *file, BlockMap *map);

void auto_save_checkpoint(int *next_wavefront_number, FILE *fp, BlockMap *map);