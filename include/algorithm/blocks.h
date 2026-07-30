#ifndef BLOCKS_H
#define BLOCKS_H

#include <mpi.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "algorithm/primitives.h"
#include "algorithm/algorithm.h"
#include "runtime/mpi_handler.h"
#include "collections/arrays.h"

#define BLOCK_HEIGHT 100
#define BLOCK_WIDTH 100

typedef struct
{
    uint32_t i;
    uint32_t j;
    bool is_unlocked;
    bool is_queued;
    // el master debe saber hasta donde va la fila y la columna para pasarselo al slave
    uint32_t width;
    uint32_t height;
    // En BlockParam son las dependencias, en BlockResult son las que se van a pasar al master
    // Tambien en el Map son las dependencias que sus vecinos usaran de el
    uint32_t row[BLOCK_WIDTH];
    uint32_t col[BLOCK_HEIGHT];
    uint32_t diag;
    MatrixCell max_cell;
} MatrixBlock;

typedef struct
{
    MatrixBlock *blocks;
    uint32_t width;
    uint32_t height;
} BlockMap;

typedef struct
{
    MatrixBlock block;
    char seq1[BLOCK_WIDTH];
    char seq2[BLOCK_HEIGHT];
} BlockParam;

typedef struct
{
    MatrixBlock block;
    MatrixCell result;
} BlockResult;

typedef struct
{
    uint32_t block_i;
    uint32_t block_j;
    uint32_t length;
    MatrixCell next_starting_cell;
    Direction next_block;
    char matched_seq1[BLOCK_WIDTH + BLOCK_HEIGHT];
    char matched_seq2[BLOCK_WIDTH + BLOCK_HEIGHT];
} TracebackResult;

BlockMap *create_Map(CharArray *seq1, CharArray *seq2);

MatrixBlock *get_MatrixBlock(uint32_t i, uint32_t j, BlockMap *map);

void print_blockMap(BlockMap *map);

void update_BlockMap(BlockResult *result_msg, BlockMap *map);

BlockParam *create_blockParam();

TracebackResult *create_tracebackResult();

void load_tracebackResult(TracebackResult *traceback_msg, MatrixCell *starting_cell, Direction next_block, BlockParam *param_msg, uint32_t traceback_length, char *matched_seq1, char *matched_seq2);

void free_TracebackResult(TracebackResult *msg);

bool block_is_ready(MatrixBlock *block, BlockMap *map);

void load_dependencies(MatrixBlock *block, BlockMap *map);

uint32_t *create_block(uint32_t width, uint32_t height);

void free_block(uint32_t *matrix);

void load_block(uint32_t *matrix, MatrixBlock *block);

void free_BlockParam(BlockParam *param);

BlockResult *create_blockResult();

void load_blockResult(BlockResult *result_msg, uint32_t *matrix, MatrixCell *max_cell, BlockParam *param_msg);

void free_BlockResult(BlockResult *msg);

MatrixBlock *get_TracebackStartingBlock(BlockMap *map);

void load_BlockParam(BlockParam *msg, MatrixBlock *block, CharArray *seq1, CharArray *seq2);

void print_info(MatrixBlock *block);

#endif