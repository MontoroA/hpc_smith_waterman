#include <stdio.h>
#include <stdlib.h>

#include "algorithm/primitives/utils.h"
#include "algorithm/primitives/list.h"

int len1 = 1000;
int len2 = 1000;

int N = 4; // N bloques por fila y columna

int block_w = len1 / N;// da un entero pero la cuenta puede dar resto, haciendo que hayan bloques que no se usen al 100%
int block_h = len2 / N;

struct block_info {
    int id;
    int size_w;
    int size_h;
    int num_rows; //porque los bloques de mas a la derecha pueden no estar 100% utilizados si len1 no es multiplo de N
    int num_cols; //porque los bloques de mas abajo pueden no estar 100% utilizados si len2 no es multiplo de N
    int* matrix;//la matriz del bloque mas el halo de la fila superior y la columna izquierda, ademas de la celda diagonal que esta incluida
};

typedef struct block_info* block;

//ya se que como maximo van a haber N bloques
block block_dscr = NULL;

for (int i = 0; i < N; i++) {
    //creamos el descriptor del bloque
    block_dscr = malloc(sizeof(struct block_info));
    block_dscr->id = i;
    block_dscr->size_w = block_w;
    block_dscr->size_h = block_h;
    block_dscr->num_rows = -1;
    block_dscr->num_cols = -1;
    block_dscr->matrix = malloc((block_dscr->size_w + 1) * (block_dscr->size_h + 1) * sizeof(int));
}

void load_block(block block_dscr, int* top_row, int* left_col, int prev_diag, int num_rows, int num_cols) {
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
}

//block_dscr es el bloque a calcular, bottom_row es la direccion en memoria donde se guardara su ultima fila, 
//right_col es la direccion en memoria donde se guardara su ultima columna
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

int max_val(int* matrix, int i, int j, char* seq1, char* seq2, int start_seq1, int start_seq2, int row_size){
    int gap_penalty = W(1);
    int similarity = s(seq1[start_seq1 + i], seq2[start_seq2 + j]);
    
    int* prev_row = matrix + ((i-1) * row_size);
    int* curr_row = matrix + (i * row_size);
    int diag = prev_row[j-1] + similarity;
    int sup = prev_row [j] + gap_penalty;
    int izq = curr_row [j-1] + gap_penalty;

    int max = diag;
    if (sup > max) max = sup;
    if (izq > max) max = izq;
    if (max < 0) max = 0;
    return max;
}