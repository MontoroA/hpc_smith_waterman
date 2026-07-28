#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "algorithm/blocks.h"
#include "algorithm/algorithm.h"


MatrixBlock *get_BlockMap(int i, int j, BlockMap *map)
{
    return &map->blocks[i * map->width + j];
}

BlockMap *create_Map(CharArray *seq1, CharArray *seq2)
{
    // last row/column of blocks might have smaller size
    int width = (seq1->length % BLOCK_WIDTH == 0) ? seq1->length / BLOCK_WIDTH : (seq1->length / BLOCK_WIDTH) + 1;
    int height = (seq2->length % BLOCK_HEIGHT == 0) ? seq2->length / BLOCK_HEIGHT : (seq2->length / BLOCK_HEIGHT) + 1;

    int length = height * width;

    BlockMap *block_map = malloc(sizeof(BlockMap));
    block_map->width = width;
    block_map->height = height;
    block_map->blocks = malloc(length * sizeof(MatrixBlock));
    for (int i_idx = 0; i_idx < height; i_idx++)
    {
        for (int j_idx = 0; j_idx < width; j_idx++)
        {
            MatrixBlock* blk = get_BlockMap(i_idx, j_idx, block_map);
            blk->i = i_idx;
            blk->j = j_idx;
            blk->is_unlocked = false;

            int start_seq1 = i_idx * BLOCK_WIDTH;
            if (start_seq1 + BLOCK_WIDTH <= seq1->length)
            {
                blk->width = BLOCK_WIDTH;
            }
            else
            {
                blk->width = seq1->length - start_seq1;
            }

            int start_seq2 = j_idx * BLOCK_HEIGHT;
            if (start_seq2 + BLOCK_HEIGHT <= seq2->length)
            {
                blk->height = BLOCK_HEIGHT;
            }
            else
            {
                blk->height = seq2->length - start_seq2;
            }
        }
    }
    return block_map;
}

void print_blockMap(BlockMap *map)
{
    int height = map->height;
    int width = map->width;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%d ", map->blocks[i * width + j].is_unlocked);
        }
        printf("\n");
    }
    printf("\n");
}

void update_BlockMap(MatrixBlock block, BlockMap *map)
{
    int i = block.i;
    int j = block.j;
    MatrixBlock *updated_block = get_BlockMap(i, j, map);

    updated_block->is_unlocked = true;
    for(int idx = 0; idx < updated_block->width; idx++)
    {
        updated_block->row[idx] = block.row[idx];
    }
    for(int idx = 0; idx < updated_block->height; idx++)
    {
        updated_block->col[idx] = block.col[idx];
    }
    updated_block->diag = block.diag;
}


bool block_is_ready(MatrixBlock *block, BlockMap *map)
{
    int i = block->i;
    int j = block->j;

    if (i == 0 && j == 0)
    {
        return true;
    }

    if (i > 0 && j > 0)
    {
        MatrixBlock *diag = &map->blocks[(i - 1) * map->width + (j - 1)];
        if (!diag->is_unlocked)
        {
            return false;
        }
    }

    if (i > 0)
    {
        MatrixBlock *sup = &map->blocks[(i - 1) * map->width + j];
        if (!sup->is_unlocked)
        {
            return false;
        }
    }

    if (j > 0)
    {
        MatrixBlock *izq = &map->blocks[i * map->width + (j - 1)];
        if (!izq->is_unlocked)
        {
            return false;
        }
    }

    return true;
}

void load_dependencies(MatrixBlock *block, BlockMap *map)
{
    int i = block->i;
    int j = block->j;

    if (i > 0 && j > 0)
    {
        MatrixBlock *diag = get_MatrixBlock(i - 1, j - 1, map);
        block->diag = diag->diag;
    }
    
    if (i > 0)
    {
        MatrixBlock *sup = get_MatrixBlock(i - 1, j, map);
        for(int idx = 0; idx < block->width; idx++)
        {
            block->row[idx] = sup->row[idx];
        }
    }
    else{
        block->diag = 0;
        for(int idx = 0; idx < block->width; idx++)
        {
            block->row[idx] = 0;
        }
    }
    
    if (j > 0)
    {
        MatrixBlock *izq = get_MatrixBlock(i, j - 1, map);
        for(int idx = 0; idx < block->height; idx++)
        {
            block->col[idx] = izq->col[idx];
        }
    }
    else
    {
        block->diag = 0;
        for(int idx = 0; idx < block->height; idx++)
        {
            block->col[idx] = 0;
        }
    }
}

int *create_block(int width, int height)
{
    int *matrix = malloc(width * height * sizeof(int));
    return matrix;
}

void free_block(int *matrix)
{
    free(matrix);
    return;
}

void load_block(int *matrix, MatrixBlock *block)
{
    matrix[0] = block->diag;
    for(int j = 0; j < block->width; j++)
    {
        matrix[j+1] = block->row[j];
    }
    for (int i = 0; i < block->height; i++)
    {
        matrix[(i + 1) * (BLOCK_WIDTH + 1)] = block->col[i];
        for(int j = 0; j < BLOCK_WIDTH; j++)
        {
            matrix[(i + 1) * (BLOCK_WIDTH+1) + (j + 1)] = 0; //TODO hace falta?
        }
    }
}

/*NO OLVIDAR QUE PARA LOS CALCULOS DE ABAJO SE TIENE EN CUENTA QUE LA MATRIX TIENE UNA FILA Y UNA COLUMNA EXTRA*/
void extract_bottom_row(BlockResult *result_msg, int *matrix)
{
    int width = result_msg->block.width;
    int height = result_msg->block.height;
    int* last_row = matrix + height * (BLOCK_WIDTH + 1) + 1;
    for(int i = 0; i < width; i++)
    {
        result_msg->block.row[i] = last_row[i];
    }
}

void extract_right_column(BlockResult *result_msg, int *matrix)
{
    int width = result_msg->block.width;
    int height = result_msg->block.height;
    int* last_col = matrix + width; //TODO: esto suma width*length(int) ?
    for (int i = 0; i < height; i++)
    {
        result_msg->block.col[i] = last_col[(i + 1) * (BLOCK_WIDTH + 1)];
    }
}

void extract_last_diagonal(BlockResult *result_msg, int *matrix)
{
    int width = result_msg->block.width;
    int height = result_msg->block.height;
    result_msg->block.diag = matrix[height * ( BLOCK_WIDTH + 1 ) + width]; // la celda diagonal es la ultima celda del bloque
}

BlockParam *create_blockParam()
{
    BlockParam *param = malloc(sizeof(BlockParam));
    return param;
}

MatrixBlock *get_MatrixBlock(int i, int j, BlockMap *map)
{
    return &map->blocks[i * map->width + j];
}

void free_BlockParam(BlockParam *param)
{
    free(param);
}

BlockResult *create_blockResult()
{
    BlockResult *msg = malloc(sizeof(BlockResult));
    return msg;
}

void load_blockResult(BlockResult *result_msg, int *matrix, MatrixCell *max_cell, BlockParam *param_msg)
{
    result_msg->result.i = max_cell->i;
    result_msg->result.j = max_cell->j;
    result_msg->result.max_score = max_cell->max_score;

    result_msg->block.i = param_msg->block.i;
    result_msg->block.j = param_msg->block.j;


    result_msg->block.width = param_msg->block.width;
    result_msg->block.height = param_msg->block.height;

    extract_bottom_row(result_msg, matrix);
    extract_right_column(result_msg, matrix);
    extract_last_diagonal(result_msg, matrix);
}

void free_BlockResult(BlockResult *msg)
{
    free(msg);
}


void print_info(MatrixBlock *block)
{
    printf("Block (%d, %d): width=%d, height=%d, is_unlocked=%d\n", block->i, block->j, block->width, block->height, block->is_unlocked);
    printf("Row: ");
    for(int i = 0; i < block->width; i++)
    {
        printf("%d ", block->row[i]);
    }
    printf("\nCol: ");
    for(int i = 0; i < block->height; i++)
    {
        printf("%d ", block->col[i]);
    }
    printf("\nDiag: %d\n\n\n", block->diag);
}