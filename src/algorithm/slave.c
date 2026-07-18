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

    BlockParam *param_msg = malloc(sizeof(BlockParam));
    BlockResult *result_msg = malloc(sizeof(BlockResult));
    int *matrix = create_block(BLOCK_WIDTH + 1, BLOCK_HEIGHT + 1);

    MPI_Status status;

    CharArray *seq1 = malloc(sizeof(CharArray));
    CharArray *seq2 = malloc(sizeof(CharArray));

    while (true)
    {
        MPI_Recv(param_msg,
                 sizeof(BlockParam),
                 MPI_BYTE,
                 MASTER_RANK,
                 TAG_BLOCK_START,
                 MPI_COMM_WORLD,
                 &status);

        if (status.MPI_TAG == TAG_TERMINATE)
        {
            break;
        }

        load_block(matrix, param_msg);

        seq1->data = param_msg->seq1;
        seq1->length = param_msg->block.width;
        seq2->data = param_msg->seq2;
        seq2->length = param_msg->block.height;

        // TODO mergear
        int *result = complete_block(matrix, seq1, seq2);
        // calculate_block(block_dscr, seq1, seq2);

        // mandar resultados
        result_msg->result.i = param_msg->block.i;
        result_msg->result.j = param_msg->block.j;
        result_msg->result.max_score = result->result.max_score;

        // TODO este indice no se si es este o otro, si es este es info repetida de result_msg->result
        result_msg->block.i = param_msg->block.i;
        result_msg->block.j = param_msg->block.j;

        // OBS: el bloque comparte el ancho del bloque de arriba a el y el alto del bloque de la izquierda a el
        result_msg->block.width = param_msg->block.width;
        result_msg->block.height = param_msg->block.height;

        extract_bottom_row(result_msg, matrix, len1, len2);
        extract_right_column(result_msg, matrix, len1, len2);
        extract_last_diagonal(result_msg, matrix, len1, len2);

        MPI_Send(result_msg,
                 sizeof(BlockResultMessage),
                 MPI_BYTE,
                 MASTER_RANK,
                 TAG_BLOCK_START,
                 MPI_COMM_WORLD);
    }
}