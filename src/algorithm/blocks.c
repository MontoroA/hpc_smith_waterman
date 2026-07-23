#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "algorithm/blocks.h"
#include "algorithm/algorithm.h"

BlockMap *create_Map(CharArray *seq1, CharArray *seq2)
{
    // last row/column of blocks might have smaller size
    int width = (seq1->length % BLOCK_WIDTH == 0) ? seq1->length / BLOCK_WIDTH : (seq1->length / BLOCK_WIDTH) + 1;
    int height = (seq2->length % BLOCK_HEIGHT == 0) ? seq2->length / BLOCK_HEIGHT : (seq2->length / BLOCK_HEIGHT) + 1;

    int length = height * width;

    MatrixBlock *map = malloc(length * sizeof(MatrixBlock));
    for (int i_idx = 0; i_idx <= height; i_idx++)
    {
        for (int j_idx = 0; j_idx <= width; j_idx++)
        {
            MatrixBlock* blk = &map[i_idx * width + j_idx];
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
    BlockMap *block_map = malloc(sizeof(BlockMap));
    block_map->blocks = map;
    block_map->width = width;
    block_map->height = height;
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

MatrixBlock *get_BlockMap(int i, int j, BlockMap *map)
{
    return &map->blocks[i * map->width + j];
}

void update_BlockMap(MatrixBlock block, BlockMap *map)
{
    int i = block.i;
    int j = block.j;

    MatrixBlock *updated_block = get_BlockMap(i, j, map);
    updated_block->is_unlocked = true; // marcar bloque como procesado

    memcpy(updated_block->row, block.row, BLOCK_WIDTH * sizeof(int));
    memcpy(updated_block->col, block.col, BLOCK_HEIGHT * sizeof(int));
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
    }else{

    }
    if (i > 0)
    {
        MatrixBlock *sup = get_MatrixBlock(i - 1, j, map);
        memcpy(block->row, sup->row, BLOCK_WIDTH * sizeof(int));
    }
    if (j > 0)
    {
        MatrixBlock *izq = get_MatrixBlock(i, j - 1, map);
        memcpy(block->col, izq->col, BLOCK_HEIGHT * sizeof(int));
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

void load_block(int *matrix, BlockParam *block_param)
{
    // cargo la diagonal de la dependencia
    matrix[0] = block_param->block.diag;
    // cargo la fila superior de la dependencia
    memcpy(matrix + 1, block_param->block.row, block_param->block.width * sizeof(int));
    // cargo el valor de la columna izquierda de la dependencia
    for (int i = 0; i < block_param->block.height; i++)
    {
        matrix[(i + 1) * BLOCK_WIDTH] = block_param->seq2[i];
    }
}

/*NO OLVIDAR QUE PARA LOS CALCULOS DE ABAJO SE TIENE EN CUENTA QUE LA MATRIX TIENE UNA FILA Y UNA COLUMNA EXTRA*/
void extract_bottom_row(BlockResult *result_msg, int *matrix, int len1, int len2)
{
    memcpy(result_msg, matrix + len2 * BLOCK_WIDTH + 1, len1 * sizeof(int));
    return;
}

void extract_right_column(BlockResult *result_msg, int *matrix, int len1, int len2)
{
    for (int i = 0; i < len2; i++)
    {
        result_msg->block.col[i] = matrix[(i + 1) * BLOCK_WIDTH + len1]; // i+1 porque la primera fila es la fila de la dependencia superior
    }
    return;
}

void extract_last_diagonal(BlockResult *result_msg, int *matrix, int len1, int len2)
{
    result_msg->block.diag = matrix[len2 * BLOCK_WIDTH + len1]; // la celda diagonal es la ultima celda del bloque
    return;
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

    // OBS: el bloque comparte el ancho del bloque de arriba a el y el alto del bloque de la izquierda a el
    result_msg->block.width = param_msg->block.width;
    result_msg->block.height = param_msg->block.height;

    extract_bottom_row(result_msg, matrix, param_msg->block.width, param_msg->block.height);
    extract_right_column(result_msg, matrix, param_msg->block.width, param_msg->block.height);
    extract_last_diagonal(result_msg, matrix, param_msg->block.width, param_msg->block.height);
}

void free_BlockResult(BlockResult *msg)
{
    free(msg);
}
