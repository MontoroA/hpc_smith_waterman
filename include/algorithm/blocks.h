#include "hpc/mpi_handler.h"
#include "algorithm/primitives/primitives.h"
#include <stdlib.h>

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
    // TODO requerido refactor. Por ahora:
    // se usan cuando MatrixBlock es param, son la row y col dependencias para procesar el bloque (i,j)
    // se usan cuando MatrixBlock es result, tienen la ultima col y la ultima row del bloque (i,j)
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
    int id;
    char seq1[BLOCK_HEIGHT];
    char seq2[BLOCK_WIDTH];
} BlockParam;

typedef struct
{
    MatrixBlock block;
    MatrixCell result;
} BlockResult;

// typedef struct
// {
//     int index_x;
//     int index_y;
//     int start_seq1; // donde arranco la seq1 con la que trabajara
//     int start_seq2; // donde arranco la seq2 con la que trabajara
//     int num_rows;   // porque los bloques de mas a la derecha pueden no estar 100% utilizados si len1 no es multiplo de N
//     int num_cols;   // porque los bloques de mas abajo pueden no estar 100% utilizados si len2 no es multiplo de N
//     int *matrix;    // la matriz del bloque mas el halo de la fila superior y la columna izquierda, ademas de la celda diagonal que esta incluida
// } BlockInfo;

// // info que se envia al slave para empezar a trabajar
// typedef struct
// {
//     int command;
//     int index_x;
//     int index_y;
//     int start_seq1;                       // donde arranco la seq1 con la que trabajara
//     int start_seq2;                       // donde arranco la seq2 con la que trabajara
//     int num_rows;                         // porque los bloques de mas a la derecha pueden no estar 100% utilizados si len1 no es multiplo de N
//     int num_cols;                         // porque los bloques de mas abajo pueden no estar 100% utilizados si len2 no es multiplo de N
//     int prev_diag;                        // la celda diagonal que es la dependencia para calcular el bloque
//     int data[BLOCK_WIDTH + BLOCK_HEIGHT]; // la fila de arriba y la columna izquierda
//     // DATA SIZE = BLOCK_WIDTH + BLOCK_HEIGHT (PARA FACILITAR MPI)
// } BlockStartMessage;

// info que se envia al master con los resultados
// typedef struct
// {
//     int index_x;
//     int index_y;
//     int last_diag;                        // la celda diagonal que es la dependencia para calcular el bloque siguiente
//     int data[BLOCK_WIDTH + BLOCK_HEIGHT]; // la ultima fila y la ultima columna del bloque calculado
// } BlockResultMessage;

BlockMap *create_blockMap(CharArray *seq1, CharArray *seq2);

MatrixBlock *get_MatrixBlock(int i, int j, BlockMap *map);

void print_blockMap(BlockMap *map);

MatrixBlock *update_BlockMap(MatrixBlock block, BlockMap *map);

MatrixBlock **get_required_neighbors(MatrixBlock *block, BlockMap *map);

BlockParam *create_blockParam();

BlockParam *load_blockParam(MatrixBlock *block, int *upper_row, int *left_col);

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

void free_BlockResult(BlockResult *msg);

// void extract_bottom_row(BlockInfo* block_dscr);

// void extract_right_column(BlockInfo* block_dscr);