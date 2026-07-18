#include <mpi.h>

#include "algorithm/slave.h"
#include "algorithm/algorithm.h"

void slave()
{
    // primero espero a que me difundan las dos secuencias
    // int len1 = -1;
    // int len2 = -1;

    /* Recibir las longitudes */
    // MPI_Bcast(&len1, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // MPI_Bcast(&len2, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // char *seq1 = malloc((len1 + 1) * sizeof(char));
    // char *seq2 = malloc((len2 + 1) * sizeof(char));

    /* Recibir las secuencias */
    // MPI_Bcast(seq1, len1 + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    // MPI_Bcast(seq2, len2 + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    BlockParam* param_msg = malloc(sizeof(BlockParam));
    BlockResult *result_msg = malloc(sizeof(BlockResult));
    int *matrix = create_block(BLOCK_WIDTH+1, BLOCK_HEIGHT+1);
    
    MPI_Status status;
    
    int *top_row = NULL;
    int *left_col = NULL;
    CharArray* seq1 = malloc(sizeof(CharArray));
    CharArray* seq2 = malloc(sizeof(CharArray));
    
    while (true)
    {
        MPI_Recv(param_msg,
                 sizeof(BlockParam),
                 MPI_BYTE,
                 MASTER_RANK,
                 TAG_BLOCK_START,
                 MPI_COMM_WORLD,
                 &status);

        if(status.MPI_TAG == TAG_TERMINATE){
            break;
        }

        top_row = param_msg->block.last_matrix_row;
        left_col = param_msg->block.last_matrix_col;
        load_block(matrix, param_msg);

        seq1->data = param_msg->seq1;
        seq1->length = param_msg->width;
        seq2->data = param_msg->seq2;
        seq2->length = param_msg->height;

        //TODO mergear
        int* result = complete_block(matrix, seq1, seq2);
        // calculate_block(block_dscr, seq1, seq2);

        // mandar resultados
        result_msg->result.i = param_msg->block.i;
        result_msg->result.j = param_msg->block.j;
        extract_bottom_row(result_msg, matrix);
        extract_right_column(result_msg, matrix);

        MPI_Send(result_msg,
                 sizeof(BlockResultMessage),
                 MPI_BYTE,
                 MASTER_RANK,
                 TAG_BLOCK_START,
                 MPI_COMM_WORLD);
    }
}