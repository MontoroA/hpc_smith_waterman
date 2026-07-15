#include <stdio.h>
#include <stdlib.h>

#include "blocks.h"
#include "algorithm.h"

//Devuelve un bloque de tamanio BLOCK_WIDTHxBLOCK_HEIGHT
block create_block(int id) {
    block block_dscr = malloc(sizeof(struct block_info));
    block_dscr->id = id;
    block_dscr->block_index.i = -1;
    block_dscr->block_index.j = -1;
    block_dscr->size_w = BLOCK_WIDTH;   
    block_dscr->size_h = BLOCK_HEIGHT;
    block_dscr->num_rows = -1;
    block_dscr->num_cols = -1;
    block_dscr->matrix = malloc((block_dscr->size_w + 1) * (block_dscr->size_h + 1) * sizeof(int));
    return block_dscr;
}

void free_block(block block_dscr) {
    free(block_dscr->matrix);
    free(block_dscr);
    return;
}

//Carga en un bloque las dependencias, su indice de bloque, y cuantas filas y columnas del bloque se van a usar.
void load_block(block block_dscr, MatrixIndex block_index, int* top_row, int* left_col, int prev_diag, int num_rows, int num_cols) {
    //cargo el indice del bloque en la matriz de bloques
    block_dscr->block_index = block_index;

    //cargo la cantidad de filas y columnas usadas del bloque
    block_dscr->num_rows = num_rows;
    block_dscr->num_cols = num_cols;

    //cargo el valor de la fila superior
    for(int j = 0; j < num_cols; j++) {
        block_dscr->matrix[j+1] = top_row[j];
    }

    //cargo el valor de la columna izquierda
    for(int i = 0; i < num_rows; i++) {
        block_dscr->matrix[(i+1) * (block_dscr->size_w + 1)] = left_col[i];
    }
    
    //cargo el valor de la diagonal anterior
    block_dscr->matrix[0] = prev_diag;
    return;
}

//block_dscr es el bloque a calcular, 
//num_rows es la cantidad de filas usadas del bloque, num_cols es la cantidad de columnas usadas del bloque
void calculate_block(block block_dscr, char* seq1, char* seq2, int start_seq1, int start_seq2) {
    //calcular el bloque
    int* matrix = block_dscr->matrix;
    int num_rows = block_dscr->num_rows;
    int num_cols = block_dscr->num_cols;

    //Complete the matrix
    int tope_block_j = num_cols + 1;//va hasta la ultima columna usada del bloque
    int max_i = 0, max_j = 0, max_score = 0;
    int k;
    int tope = num_rows + num_cols;
    for(k = 0 ; k <= tope ; k++){
        int init_i = min(k, num_rows);
        int stop_i = max(1, k - num_cols + 2);
        for(int i = init_i ; i >= stop_i ; i--){
            int j = k-i;
            matrix[i*tope_block_j + j] = max_val(matrix, i, j, seq1, seq2, start_seq1, start_seq2, tope_block_j);
            if(matrix[i*tope_block_j + j] > max_score){
                max_score = matrix[i*tope_block_j + j];
                max_i = i;
                max_j = j;
            }
        }
    }
    return;
}

//carga en la direccion bottom_row la ultima fila usada del bloque
void extract_bottom_row(block block_dscr, int* bottom_row) {
    int num_rows = block_dscr->num_rows;
    int num_cols = block_dscr->num_cols;
    for(int j = 0; j < num_cols; j++) {
        bottom_row[j] = block_dscr->matrix[(num_rows - 1) * (num_cols - 1) + (j+1)]; //j+1 porque la primera columna es la columna de la dependencia izquierda
    }
    return;
}

//carga en la direccion right_col la ultima columna usada del bloque
void extract_right_column(block block_dscr, int* right_col) {
    int num_rows = block_dscr->num_rows;
    int num_cols = block_dscr->num_cols;
    for(int i = 0; i < num_rows; i++) {
        right_col[i] = block_dscr->matrix[(i+1) * (num_cols - 1)]; //i+1 porque la primera fila es la fila de la dependencia superior
    }
    return;
}

//carga en la direccion last_diagonal la ultima celda de la diagonal del bloque
void extract_last_diagonal(block block_dscr, int* last_diagonal) {
    int num_rows = block_dscr->num_rows;
    int num_cols = block_dscr->num_cols;
    last_diagonal = block_dscr->matrix[num_rows * num_cols]; //la celda diagonal es la ultima celda del bloque
    return;
}