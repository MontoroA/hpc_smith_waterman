#include <stdio.h>
#include <stdlib.h>

#include "algorithm/blocks.h"
#include "algorithm/algorithm.h"

BlockMap *create_blockMap(CharArray *seq1, CharArray *seq2)
{
    // last row/column of blocks might have smaller size
    // TODO por que -1?
    int height = (seq1->length + BLOCK_HEIGHT - 1) / BLOCK_HEIGHT;
    int width = (seq2->length + BLOCK_WIDTH - 1) / BLOCK_WIDTH;
    int length = height * width;

    MatrixBlock *map = malloc(length * sizeof(MatrixBlock));
    for (int i_idx = 0; i_idx <= height; i_idx++)
    {
        for (int j_idx = 0; j_idx <= width; j_idx++)
        {
            MatrixBlock blk = (MatrixBlock)map[i_idx * width + j_idx];
            blk.i = i_idx;
            blk.j = j_idx;
            blk.is_unlocked = false;
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

MatrixBlock *update_BlockMap(MatrixBlock block, BlockMap *map)
{
    // Se agrega info de la fila y columna del bloque procesado
    int i = block.i;
    int j = block.j;

    map->blocks[i * map->width + j].is_unlocked = true; // marcar bloque como procesado

    // comparte las dimensiones de sus bloques vecinos
    map->blocks[i * map->width + j].width = block.width;
    map->blocks[i * map->width + j].height = block.height;

    memcpy(map->blocks[i * map->width + j].row, block.row, BLOCK_WIDTH * sizeof(int));
    memcpy(map->blocks[i * map->width + j].col, block.col, BLOCK_HEIGHT * sizeof(int));
    map->blocks[i * map->width + j].diag = block.diag;

    MatrixBlock *inf = &map->blocks[(i + 1) * map->width + j];
    MatrixBlock *diag = &map->blocks[(i + 1) * map->width + (j + 1)];
    MatrixBlock *der = &map->blocks[i * map->width + (j + 1)];

    // TODO
    // Mirar el bloque recibido: puede habilitar a los siguientes: abajo, derecha, siguiente en diagonal
    // Mirar map para eso, obtener
}

void load_dependencies(MatrixBlock *block, BlockMap *map)
{
    int i = block->i;
    int j = block->j;

    // TODO chequear que no me pase de los bordes de la matriz
    MatrixBlock *sup = &map->blocks[(i - 1) * map->width + j];
    MatrixBlock *diag = &map->blocks[(i - 1) * map->width + (j - 1)];
    MatrixBlock *izq = &map->blocks[i * map->width + (j - 1)];

    memcpy(block->row, sup->row, BLOCK_WIDTH * sizeof(int));
    memcpy(block->col, izq->col, BLOCK_HEIGHT * sizeof(int));
    diag->diag = diag->diag;
}

BlockParam *create_blockParam(MatrixBlock *block, int *upper_row, int *left_col)
{
    // BlockParam* block_param = malloc(sizeof(BlockParam) + (BLOCK_WIDTH + BLOCK_HEIGHT) * sizeof(int));
    // block_param->block = *block;
    // for(int j = 0; j < BLOCK_WIDTH; j++) {
    //     block_param->uppper_row[j] = upper_row[j];
    // }
    // for(int i = 0; i < BLOCK_HEIGHT; i++) {
    //     block_param->left_col[i] = left_col[i];
    // }
    // return block_param;
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

// TODO este metodo va si el worker ya tiene toda la secuencia
// Carga en un bloque las dependencias, su indice de bloque, y cuantas filas y columnas del bloque se van a usar.
// void load_block(BlockInfo *block_dscr, int index_x, int index_y, int start_seq1, int start_seq2, int num_rows,
//                 int num_cols, int *top_row, int *left_col, int prev_diag)
// {
//     // cargo el indice del bloque en la matriz de bloques
//     block_dscr->index_x = index_x;
//     block_dscr->index_y = index_y;

//     // cargo el indice de la secuencia 1 y 2 donde empieza el bloque
//     block_dscr->start_seq1 = start_seq1;
//     block_dscr->start_seq2 = start_seq2;

//     // cargo la cantidad de filas y columnas usadas del bloque
//     block_dscr->num_rows = num_rows;
//     block_dscr->num_cols = num_cols;

//     // cargo el valor de la fila superior, memcpy es mas rapido
//     memcpy(block_dscr->matrix + 1, top_row, num_cols * sizeof(int));

//     // cargo el valor de la columna izquierda
//     for (int i = 0; i < num_rows; i++)
//     {
//         block_dscr->matrix[(i + 1) * BLOCK_WIDTH] = left_col[i];
//     }

//     // cargo el valor de la diagonal anterior
//     block_dscr->matrix[0] = prev_diag;
//     return;
// }

// block_dscr es el bloque a calcular,
// num_rows es la cantidad de filas usadas del bloque, num_cols es la cantidad de columnas usadas del bloque
/*void calculate_block(BlockInfo *block_dscr, char *seq1, char *seq2)
{
    // calcular el bloque
    int *matrix = block_dscr->matrix;
    int start_seq1 = block_dscr->start_seq1;
    int start_seq2 = block_dscr->start_seq2;
    int num_rows = block_dscr->num_rows;
    int num_cols = block_dscr->num_cols;

    // Complete the matrix
    int tope_block_j = num_cols + 1; // va hasta la ultima columna usada del bloque
    int max_i = 0, max_j = 0, max_score = 0;
    int k;
    int tope = num_rows + num_cols;
    for (k = 0; k <= tope; k++)
    {
        int init_i = min(k, num_rows);
        int stop_i = max(1, k - num_cols + 2);
        for (int i = init_i; i >= stop_i; i--)
        {
            int j = k - i;
            matrix[i * tope_block_j + j] = max_val(matrix, i, j, seq1, seq2, start_seq1, start_seq2, tope_block_j);
            if (matrix[i * tope_block_j + j] > max_score)
            {
                max_score = matrix[i * tope_block_j + j];
                max_i = i;
                max_j = j;
            }
        }
    }
    return;
}*/

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

void free_BlockResult(BlockResult *msg)
{
    free(msg);
}

// void extract_bottom_row(int *matrix, BlockResult *block_dscr)
// {
//     // TODO
// }

// carga en la direccion right_col la ultima columna usada del bloque
// void extract_right_column(int *matrix, BlockResult *block_dscr)
// {
//     // TODO
// }