#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "algorithm/blocks.h"
#include "collections/arrays.h"
#include "algorithm/algorithm.h"

MatrixBlock *get_BlockMap(uint32_t i, uint32_t j, BlockMap *map)
{
    return &map->blocks[i * map->width + j];
}

MatrixBlock *get_MatrixBlock(uint32_t i, uint32_t j, BlockMap *map)
{
    return &map->blocks[i * map->width + j];
}

BlockMap *create_Map(CharArray *seq1, CharArray *seq2)
{
    // last row/column of blocks might have smaller size
    uint32_t width = (seq1->length % BLOCK_WIDTH == 0) ? seq1->length / BLOCK_WIDTH : (seq1->length / BLOCK_WIDTH) + 1;
    uint32_t height = (seq2->length % BLOCK_HEIGHT == 0) ? seq2->length / BLOCK_HEIGHT : (seq2->length / BLOCK_HEIGHT) + 1;

    uint32_t length = height * width;

    BlockMap *block_map = malloc(sizeof(BlockMap));
    block_map->width = width;
    block_map->height = height;
    block_map->blocks = malloc(length * sizeof(MatrixBlock));
    for (uint32_t i_idx = 0; i_idx < height; i_idx++)
    {
        for (uint32_t j_idx = 0; j_idx < width; j_idx++)
        {
            MatrixBlock *blk = get_BlockMap(i_idx, j_idx, block_map);
            blk->i = i_idx;
            blk->j = j_idx;
            blk->is_unlocked = false;
            blk->is_queued = false;

            uint32_t start_seq1 = j_idx * BLOCK_WIDTH;
            if (start_seq1 + BLOCK_WIDTH <= seq1->length)
            {
                blk->width = BLOCK_WIDTH;
            }
            else
            {
                blk->width = seq1->length - start_seq1;
            }

            uint32_t start_seq2 = i_idx * BLOCK_HEIGHT;
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
    uint32_t height = map->height;
    uint32_t width = map->width;

    for (uint32_t i = 0; i < height; i++)
    {
        for (uint32_t j = 0; j < width; j++)
        {
            printf("%d ", get_MatrixBlock(i, j, map)->is_unlocked);
        }
        printf("\n");
    }
    printf("\n");
}

void update_BlockMap(BlockResult *result_msg, BlockMap *map)
{
    uint32_t i = result_msg->block.i;
    uint32_t j = result_msg->block.j;
    MatrixBlock *updated_block = get_MatrixBlock(i, j, map);

    updated_block->is_unlocked = true;
    for (uint32_t idx = 0; idx < updated_block->width; idx++)
    {
        updated_block->row[idx] = result_msg->block.row[idx];
    }
    for (uint32_t idx = 0; idx < updated_block->height; idx++)
    {
        updated_block->col[idx] = result_msg->block.col[idx];
    }
    updated_block->diag = result_msg->block.diag;
    updated_block->max_cell.i = result_msg->result.i;
    updated_block->max_cell.j = result_msg->result.j;
    updated_block->max_cell.max_score = result_msg->result.max_score;
}

bool block_is_ready(MatrixBlock *block, BlockMap *map)
{
    uint32_t i = block->i;
    uint32_t j = block->j;

    if (i == 0 && j == 0)
    {
        return true;
    }

    if (i > 0 && j > 0)
    {
        MatrixBlock *diag = get_MatrixBlock(i - 1, j - 1, map); //&map->blocks[(i - 1) * map->width + (j - 1)];
        if (!diag->is_unlocked)
        {
            return false;
        }
    }

    if (i > 0)
    {
        MatrixBlock *sup = get_MatrixBlock(i - 1, j, map); //&map->blocks[(i - 1) * map->width + j];
        if (!sup->is_unlocked)
        {
            return false;
        }
    }

    if (j > 0)
    {
        MatrixBlock *izq = get_MatrixBlock(i, j - 1, map); //&map->blocks[i * map->width + (j - 1)];
        if (!izq->is_unlocked)
        {
            return false;
        }
    }

    return true;
}

void load_dependencies(MatrixBlock *block, BlockMap *map)
{
    uint32_t i = block->i;
    uint32_t j = block->j;

    if (i > 0 && j > 0)
    {
        MatrixBlock *diag = get_MatrixBlock(i - 1, j - 1, map);
        block->diag = diag->diag;
    }

    if (i > 0)
    {
        MatrixBlock *sup = get_MatrixBlock(i - 1, j, map);
        for (uint32_t idx = 0; idx < block->width; idx++)
        {
            block->row[idx] = sup->row[idx];
        }
    }
    else
    {
        block->diag = 0;
        for (uint32_t idx = 0; idx < block->width; idx++)
        {
            block->row[idx] = 0;
        }
    }

    if (j > 0)
    {
        MatrixBlock *izq = get_MatrixBlock(i, j - 1, map);
        for (uint32_t idx = 0; idx < block->height; idx++)
        {
            block->col[idx] = izq->col[idx];
        }
    }
    else
    {
        block->diag = 0;
        for (uint32_t idx = 0; idx < block->height; idx++)
        {
            block->col[idx] = 0;
        }
    }
}

uint32_t *create_block(uint32_t width, uint32_t height)
{
    uint32_t *matrix = malloc(width * height * sizeof(uint32_t));
    return matrix;
}

void free_block(uint32_t *matrix)
{
    free(matrix);
    return;
}

void load_block(uint32_t *matrix, MatrixBlock *block)
{
    matrix[0] = block->diag;
    for (uint32_t j = 0; j < block->width; j++)
    {
        matrix[j + 1] = block->row[j];
    }
    for (uint32_t i = 0; i < block->height; i++)
    {
        matrix[(i + 1) * (BLOCK_WIDTH + 1)] = block->col[i];
        for (uint32_t j = 0; j < BLOCK_WIDTH; j++)
        {
            matrix[(i + 1) * (BLOCK_WIDTH + 1) + (j + 1)] = 0; // TODO hace falta?
        }
    }
}

/*NO OLVIDAR QUE PARA LOS CALCULOS DE ABAJO SE TIENE EN CUENTA QUE LA MATRIX TIENE UNA FILA Y UNA COLUMNA EXTRA*/
void extract_bottom_row(BlockResult *result_msg, uint32_t *matrix)
{
    uint32_t width = result_msg->block.width;
    uint32_t height = result_msg->block.height;
    uint32_t *last_row = matrix + height * (BLOCK_WIDTH + 1) + 1;
    for (uint32_t i = 0; i < width; i++)
    {
        result_msg->block.row[i] = last_row[i];
    }
}

void extract_right_column(BlockResult *result_msg, uint32_t *matrix)
{
    uint32_t width = result_msg->block.width;
    uint32_t height = result_msg->block.height;
    uint32_t *last_col = matrix + width; // TODO: esto suma width*length(int) ?
    for (uint32_t i = 0; i < height; i++)
    {
        result_msg->block.col[i] = last_col[(i + 1) * (BLOCK_WIDTH + 1)];
    }
}

void extract_last_diagonal(BlockResult *result_msg, uint32_t *matrix)
{
    uint32_t width = result_msg->block.width;
    uint32_t height = result_msg->block.height;
    result_msg->block.diag = matrix[height * (BLOCK_WIDTH + 1) + width]; // la celda diagonal es la ultima celda del bloque
}

BlockParam *create_blockParam()
{
    BlockParam *param = malloc(sizeof(BlockParam));
    return param;
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

void load_blockResult(BlockResult *result_msg, uint32_t *matrix, MatrixCell *max_cell, BlockParam *param_msg)
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
    for (uint32_t i = 0; i < block->width; i++)
    {
        printf("%d ", block->row[i]);
    }
    printf("\nCol: ");
    for (uint32_t i = 0; i < block->height; i++)
    {
        printf("%d ", block->col[i]);
    }
    printf("\nDiag: %d\n\n\n", block->diag);
}

TracebackResult *create_tracebackResult()
{
    TracebackResult *msg = malloc(sizeof(TracebackResult));
    return msg;
}

void load_tracebackResult(TracebackResult *traceback_msg, MatrixCell *starting_cell, Direction next_block, BlockParam *param_msg, uint32_t traceback_length, char *matched_seq1, char *matched_seq2)
{
    traceback_msg->block_i = param_msg->block.i;
    traceback_msg->block_j = param_msg->block.j;
    traceback_msg->length = traceback_length;
    traceback_msg->next_starting_cell = *starting_cell;
    traceback_msg->next_block = next_block;

    memcpy(traceback_msg->matched_seq1, matched_seq1, traceback_msg->length);
    memcpy(traceback_msg->matched_seq2, matched_seq2, traceback_msg->length);
}

void free_TracebackResult(TracebackResult *msg)
{
    free(msg);
}

MatrixBlock *get_TracebackStartingBlock(BlockMap *map)
{
    uint32_t max_val = 0;
    MatrixBlock *block = NULL;

    for (uint32_t i = 0; i < map->height; i++)
    {
        for (uint32_t j = 0; j < map->width; j++)
        {
            MatrixBlock *current_block = get_MatrixBlock(i, j, map);
            if (current_block->max_cell.max_score > max_val)
            {
                max_val = current_block->max_cell.max_score;
                block = current_block;
            }
        }
    }
    return block;
}

void load_BlockParam(BlockParam *msg, MatrixBlock *block, CharArray *seq1, CharArray *seq2)
{
    msg->block = *block;
    memcpy(msg->seq1, seq1->data + block->j * BLOCK_WIDTH, block->width);
    memcpy(msg->seq2, seq2->data + block->i * BLOCK_HEIGHT, block->height);
}
