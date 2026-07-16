#include "hpc/mpi_handler.h"
#include "algorithm/primitives/primitives.h"


typedef struct {
    int i;
    int j;
    int max_score;
} MatrixCell;

typedef struct {
    int i;
    int j;
    bool is_unlocked;
    //TODO requerido refactor. Por ahora: 
    //se usan cuando MatrixBlock es param, son la row y col dependencias para procesar el bloque (i,j)
    //se usan cuando MatrixBlock es result, tienen la ultima col y la ultima row del bloque (i,j)
    int last_matrix_row[BLOCK_WIDTH];  
    int last_matrix_col[BLOCK_HEIGHT];
} MatrixBlock;


typedef struct {
    MatrixBlock* blocks;
    int width;
    int height;
} BlockMap;

typedef struct {
    MatrixBlock block;
    int id;
    int width;
    int height;
    char seq1[BLOCK_HEIGHT];
    char seq2[BLOCK_WIDTH];
} BlockParam;

typedef struct {
    MatrixBlock block;
    MatrixCell result;
} BlockResult;


typedef struct {
    int id;
    MatrixBlock block_index; //indice del bloque en la matriz de bloques
    int start_seq1; //indice de la secuencia 1 donde empieza el bloque
    int start_seq2; //indice de la secuencia 2 donde empieza el bloque
    int num_rows; //porque los bloques de mas a la derecha pueden no estar 100% utilizados si len1 no es multiplo de N
    int num_cols; //porque los bloques de mas abajo pueden no estar 100% utilizados si len2 no es multiplo de N
    int* matrix;//la matriz del bloque mas el halo de la fila superior y la columna izquierda, ademas de la celda diagonal que esta incluida
} BlockInfo;




BlockMap* create_blockMap(CharArray* seq1, CharArray* seq2);
void print_blockMap(BlockMap* map);
MatrixBlock* update_BlockMap(MatrixBlock block, BlockMap* map);
MatrixBlock** get_required_neighbors(MatrixBlock block, BlockMap* map);

BlockParam* create_blockParam(MatrixBlock* block, int* upper_row, int* left_col);

// BlockInfo* create_block(int id);
// void free_block(BlockInfo* block_dscr);
void load_block(int* matrix, BlockParam* block_param);
// void load_block(BlockInfo* block_dscr, MatrixBlock block_index,  int start_seq1, int start_seq2,  int num_rows, int num_cols, int* top_row, int* left_col, int prev_diag);
void calculate_block(BlockInfo* block_dscr, char* seq1, char* seq2);
// void extract_bottom_row(BlockInfo* block_dscr, int* bottom_row);
// void extract_right_column(BlockInfo* block_dscr, int* right_col);
void extract_bottom_row(int* matrix, BlockResult* block_dscr);
void extract_right_column(int* matrix, BlockResult* block_dscr);
// void extract_last_diagonal(BlockInfo* block_dscr, int* last_diagonal);