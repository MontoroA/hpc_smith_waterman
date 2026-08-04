#include "../../include/runtime/checkpoint.h"

FILE *create_checkpoint_file(const char *filename)
{
    FILE *file = fopen(filename, "wb+");
    if (!file)
    {
        perror("Failed to create checkpoint file");
        return NULL;
    }

    CheckpointHeader header;
    header.last_wavefront_computed = 0;
    if (fseek(file, 0, SEEK_SET) != 0)
    {
        perror("fseek");
        fclose(file);
        return NULL;
    }

    if (fwrite(&header, sizeof(CheckpointHeader), 1, file) != 1)
    {
        perror("fwrite");
        fclose(file);
        return NULL;
    }

    //logging(MASTER_RANK, "Created checkpoint file: %s\n", filename);
    return file;
}

FILE *open_checkpoint_file(const char *filename)
{
    FILE *file = fopen(filename, "rb+");
    if (!file)
    {
        perror("Failed to open checkpoint file");
        return NULL;
    }

    //logging(MASTER_RANK, "Opened checkpoint file: %s\n", filename);
    return file;
}

int save_wavefront_to_checkpoint(FILE *file, uint32_t wavefront_number, BlockMap *map)
{
    for (uint32_t i = 0; i < map->height && i <= wavefront_number; i++)
    {
        uint32_t j = wavefront_number - i;
        if (j < map->width) // && j >= 0
        {
            MatrixBlock *block = get_MatrixBlock(i, j, map);
            uint32_t block_number = i * map->width + j;
            long offset = sizeof(CheckpointHeader) + block_number * sizeof(MatrixBlock);

            if (fseek(file, offset, SEEK_SET) != 0)
            {
                perror("fseek");
                return -1;
            }

            if (fwrite(block, sizeof(MatrixBlock), 1, file) != 1)
            {
                perror("fwrite");
                return -1;
            }
        }
    }

    CheckpointHeader header;
    header.last_wavefront_computed = wavefront_number;
    if (fseek(file, 0, SEEK_SET) != 0)
    {
        perror("fseek");
        return -1;
    }

    if (fwrite(&header, sizeof(CheckpointHeader), 1, file) != 1)
    {
        perror("fwrite");
        return -1;
    }

    //logging(MASTER_RANK, "Saved wavefront %d to checkpoint\n", wavefront_number);
    return 0;
}

int load_from_checkpoint(FILE *file, BlockMap *map)
{
    //logging(MASTER_RANK, "Loading from checkpoint...\n");

    if (fseek(file, 0, SEEK_SET) != 0)
    {
        perror("fseek");
        return -1;
    }

    CheckpointHeader header;
    if (fread(&header, sizeof(CheckpointHeader), 1, file) != 1)
    {
        perror("fread");
        return -1;
    }

    uint32_t last_wavefront_computed = header.last_wavefront_computed;

    for (uint32_t i = 0; i < map->height; i++)
    {
        for (uint32_t j = 0; j < map->width; j++)
        {
            if (i + j <= last_wavefront_computed)
            {
                MatrixBlock *block = get_MatrixBlock(i, j, map);
                uint32_t block_number = i * map->width + j;
                long offset = sizeof(CheckpointHeader) + block_number * sizeof(MatrixBlock);

                if (fseek(file, offset, SEEK_SET) != 0)
                {
                    perror("fseek");
                    return -1;
                }

                if (fread(block, sizeof(MatrixBlock), 1, file) != 1)
                {
                    perror("fread");
                    return -1;
                }
                block->is_unlocked = true;
                //logging(MASTER_RANK, "Loaded block (%d, %d) from checkpoint\n", i, j);
            }
        }
    }
    //logging(MASTER_RANK, "Loaded from checkpoint: last_wavefront_computed = %d\n", last_wavefront_computed); // TODO checkear que dice que retomo de la penultima y no de la ultima raro
    return last_wavefront_computed;
}

void auto_save_checkpoint(uint32_t *next_wavefront_number, FILE *fp, BlockMap *map)
{
    for (uint32_t i = 0; i < map->height && i <= *next_wavefront_number; i++)
    {
        uint32_t j = *next_wavefront_number - i;
        if (j < map->width) // && j >= 0
        {
            MatrixBlock *block = get_MatrixBlock(i, j, map);
            if (block->is_unlocked != true)
            {
                return;
            }
        }
    }
    int res = save_wavefront_to_checkpoint(fp, *next_wavefront_number, map);
    if (res != -1)
    {
        *next_wavefront_number += CHECKPOINT_INTERVAL;
    }
}