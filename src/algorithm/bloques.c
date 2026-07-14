int len1 = 1000;
int len2 = 1000;

int N = 4; // N bloques por fila y columna

int block_w = len1 / N;// da un entero pero la cuenta puede dar resto, haciendo que hayan bloques que no se usen al 100%
int block_h = len2 / N;

struct block_info {
    int id;
    int size_w;
    int size_h;
    int max_i; //porque los bloques de mas a la derecha pueden no estar 100% utilizados si len1 no es multiplo de N
    int max_j; //porque los bloques de mas abajo pueden no estar 100% utilizados si len2 no es multiplo de N
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
    block_dscr->max_i = -1;
    block_dscr->max_j = -1;
    block_dscr->top_row = malloc(block_dscr->size_w * sizeof(int));
    block_dscr->left_col = malloc(block_dscr->size_h * sizeof(int));
    block_dscr->matrix = malloc(block_dscr->size_w * block_dscr->size_h * sizeof(int));

    //agregamos el descriptor del bloque al arreglo de bloques
    blocks_array[i] = block_dscr;
}

void load_block(block block_dscr, int* top_row, int* left_col, int max_i, int max_j) {
    block_dscr->top_row = top_row;
    block_dscr->left_col = left_col;
    block_dscr->max_i = max_i;
    block_dscr->max_j = max_j;
}