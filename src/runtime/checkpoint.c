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

    return file;
}

int save_wavefront_to_checkpoint(FILE *file, int wavefront_number, BlockMap *map)
{
    for (int i = 0; i < map->height && i <= wavefront_number; i++)
    {
        int j = wavefront_number - i;
        if (j >= 0 && j < map->width)
        {
            MatrixBlock *block = get_MatrixBlock(i, j, map);
            int block_number = i * map->width + j;
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
    return 0;
}

void load_from_checkpoint(const char *filename, BlockMap *map)
{
    FILE *file = fopen(filename, "rb");

    if (fseek(file, 0, SEEK_SET) != 0)
    {
        perror("fseek");
        return;
    }

    CheckpointHeader header;
    if (fread(&header, sizeof(CheckpointHeader), 1, file) != 1)
    {
        perror("fread");
        return;
    }

    int last_wavefront_computed = header.last_wavefront_computed;

    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            if (i + j <= last_wavefront_computed)
            {
                MatrixBlock *block = get_MatrixBlock(i, j, map);
                int block_number = i * map->width + j;
                long offset = sizeof(CheckpointHeader) + block_number * sizeof(MatrixBlock);

                if (fseek(file, offset, SEEK_SET) != 0)
                {
                    perror("fseek");
                    return;
                }

                if (fread(block, sizeof(MatrixBlock), 1, file) != 1)
                {
                    perror("fread");
                    return;
                }
            }
        }
    }
}

void auto_save_checkpoint(int *next_wavefront_number, FILE *fp, BlockMap *map)
{
    for (int i = 0; i < map->height && i <= *next_wavefront_number; i++)
    {
        int j = *next_wavefront_number - i;
        if (j >= 0 && j < map->width)
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
        *next_wavefront_number += 2;
    }
}