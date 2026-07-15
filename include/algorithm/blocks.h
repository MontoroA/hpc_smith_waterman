#include "../hpc/mpi_handler.h"
#include "primitives.h"

struct block_info {
    int id;
    MatrixIndex block_index; //indice del bloque en la matriz de bloques
    int start_seq1; //indice de la secuencia 1 donde empieza el bloque
    int start_seq2; //indice de la secuencia 2 donde empieza el bloque
    int num_rows; //porque los bloques de mas a la derecha pueden no estar 100% utilizados si len1 no es multiplo de N
    int num_cols; //porque los bloques de mas abajo pueden no estar 100% utilizados si len2 no es multiplo de N
    int* matrix;//la matriz del bloque mas el halo de la fila superior y la columna izquierda, ademas de la celda diagonal que esta incluida
};

typedef struct block_info* block;

block create_block(int id);

void free_block(block block_dscr);

void load_block(block block_dscr, MatrixIndex block_index,  int start_seq1, int start_seq2,  int num_rows, int num_cols, int* top_row, int* left_col, int prev_diag);

void calculate_block(block block_dscr, char* seq1, char* seq2);

void extract_bottom_row(block block_dscr, int* bottom_row);

void extract_right_column(block block_dscr, int* right_col);

void extract_last_diagonal(block block_dscr, int* last_diagonal);