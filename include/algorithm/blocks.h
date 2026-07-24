#ifndef BLOCKS_H
#define BLOCKS_H

#include <stdlib.h>

#include "hpc/mpi_handler.h"
#include "algorithm/primitives/primitives.h"

typedef struct
{
    int i;
    int j;
    int max_score;
} MatrixCell;

typedef struct
{
    int i;
    int j;
    bool is_unlocked;
    // el master debe saber hasta donde va la fila y la columna para pasarselo al slave
    int width;
    int height;
    // En BlockParam son las dependencias, en BlockResult son las que se van a pasar al master
    // Tambien en el Map son las dependencias que sus vecinos usaran de el
    int row[BLOCK_WIDTH];
    int col[BLOCK_HEIGHT];
    int diag;
} MatrixBlock;

typedef struct
{
    MatrixBlock *blocks;
    int width;
    int height;
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
    int block_i;
    int block_j;
    int width;
    int height;
    MatrixCell next_starting_cell;
    Direction next_block;
    char matched_seq1[BLOCK_WIDTH];
    char matched_seq2[BLOCK_HEIGHT];
} TracebackResult;

BlockMap *create_Map(CharArray *seq1, CharArray *seq2);

MatrixBlock *get_MatrixBlock(int i, int j, BlockMap *map);

void print_blockMap(BlockMap *map);

void update_BlockMap(MatrixBlock block, BlockMap *map);

MatrixBlock **get_required_neighbors(MatrixBlock *block, BlockMap *map);

BlockParam *create_blockParam();

TracebackResult *create_tracebackResult();

void load_tracebackResult(TracebackResult *traceback_msg, MatrixCell *starting_cell, Direction next_block, BlockParam *param_msg, char *matched_seq1, char *matched_seq2)

    void free_TracebackResult(TracebackResult *msg);

// BlockParam *load_blockParam(MatrixBlock *block, int *upper_row, int *left_col);

bool block_is_ready(MatrixBlock *block, BlockMap *map);

void load_dependencies(MatrixBlock *block, BlockMap *map);

int *create_block(int width, int height);

void free_block(int *block_dscr);

void load_block(int *matrix, BlockParam *block_param);

// void load_block(BlockInfo *block_dscr, int index_x, int index_y, int start_seq1, int start_seq2, int num_rows, int num_cols, int *top_row, int *left_col, int prev_diag);

// void calculate_block(BlockInfo *block_dscr, char *seq1, char *seq2);

void extract_bottom_row(BlockResult *result_msg, int *matrix, int len1, int len2);

void extract_right_column(BlockResult *result_msg, int *matrix, int len1, int len2);

void extract_last_diagonal(BlockResult *result_msg, int *matrix, int len1, int len2);

// BlockStartMessage *create_block_start_message();

void free_BlockParam(BlockParam *param);

BlockResult *create_blockResult();

void load_blockResult(BlockResult *result_msg, int *matrix, MatrixCell *max_cell, BlockParam *param_msg);

void free_BlockResult(BlockResult *msg);

// void extract_bottom_row(BlockInfo* block_dscr);

// void extract_right_column(BlockInfo* block_dscr);

#endif