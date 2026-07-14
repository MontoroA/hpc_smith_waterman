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
    int* top_row;
    int* left_col;
    int* matrix;
};

typedef struct block_info* block;

//ya se que como maximo van a haber N bloques
block blocks_array[N];//son punteros al struct block_info que es el descriptor del bloque
block block_dscr = NULL;

for (int i = 0; i < N; i++) {
    //creamos el descriptor del bloque
    block_dscr = malloc(sizeof(struct block_info));
    block_dscr->id = i;
    block_dscr->size_w = block_w;
    block_dscr->size_h = block_h;
    block_dscr->num_rows = -1;
    block_dscr->num_cols = -1;
    block_dscr->top_row = malloc(block_dscr->size_w * sizeof(int));
    block_dscr->left_col = malloc(block_dscr->size_h * sizeof(int));
    block_dscr->matrix = malloc(block_dscr->size_w * block_dscr->size_h * sizeof(int));

    //agregamos el descriptor del bloque al arreglo de bloques
    blocks_array[i] = block_dscr;
}

void load_block(block block_dscr, int* top_row, int* left_col, int max_i, int max_j) {
    block_dscr->top_row = top_row;
    block_dscr->left_col = left_col;
    block_dscr->num_rows = num_rows;
    block_dscr->num_cols = num_cols;
}

//block_dscr es el bloque a calcular, bottom_row es la direccion en memoria donde se guardara su ultima fila, 
//right_col es la direccion en memoria donde se guardara su ultima columna
void calculate_block(block block_dscr, int* bottom_row, int* right_col, int &num_rows, int &num_cols) {

    /*
    ----Calcular el bloque----
    hay que cambiar el algoritmo porque se toma como fila 0 y columna 0 
    las block_dscr->top_row y block_dscr->left_col
    */


    //se toma como la ultima fila la que realmente se usa y la columna de mas a la derecha la que realmente se usa
    //que se reprentan con num_rows(cantidad de filas usadas) y num_cols(cantidad de columnas usadas)
    bottom_row_ptr = block_dscr->matrix + ((num_rows - 1) * size_w);//me paro en la ultima fila usada del bloque
    for (int j = 0; j < size_w; j++) {
        bottom_row[j] = bottom_row_ptr + j; //muevo el puntero a la siguiente columna (itero en la fila)
    }

    right_col_ptr = block_dscr->matrix + (num_cols - 1);//me paro en la ultima columna usada del bloque
    for(int i = 0; i < size_h; i++) {
        right_col[i] = right_col_ptr + (i * size_w); //muevo el puntero a la siguiente fila (itero en la columna)
    }

    num_rows = block_dscr->num_rows;
    num_cols = block_dscr->num_cols;
    return;
}