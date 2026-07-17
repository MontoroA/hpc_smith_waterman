#include "algorithm/slave.h"
#include <mpi.h>

void work()
{
    // primero espero a que me difundan las dos secuencias
    int len1 = -1;
    int len2 = -1;

    /* Recibir las longitudes */
    MPI_Bcast(&len1, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&len2, 1, MPI_INT, 0, MPI_COMM_WORLD);

    char *seq1 = malloc((len1 + 1) * sizeof(char));
    char *seq2 = malloc((len2 + 1) * sizeof(char));

    /* Recibir las secuencias */
    MPI_Bcast(seq1, len1 + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(seq2, len2 + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    BlockStartMessage *start_msg = malloc(sizeof(BlockStartMessage));
    BlockResultMessage *result_msg = malloc(sizeof(BlockResultMessage));
    BlockInfo *block_dscr = create_block();

    int *top_row = NULL;
    int *left_col = NULL;

    while (true)
    {
        MPI_Recv(start_msg,
                 sizeof(BlockStartMessage),
                 MPI_BYTE,
                 MASTER_RANK,
                 TAG_BLOCK_START,
                 MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        int command = start_msg->command; //-> del receive el comando 0 es ejecutar, 1 es terminar proceso
        if (command == 1)
        {
            free_block(block_dscr);
            free(sequences);
            break;
        }

        top_row = start_msg->data;
        left_col = start_msg->data + BLOCK_WIDTH;

        load_block(block_dscr, start_msg->index_x, start_msg->index_y,
                   start_msg->start_seq1, start_msg->start_seq2,
                   start_msg->num_rows, start_msg->num_cols, top_row, left_col, start_msg->prev_diag);

        // calcular bloque
        calculate_block(block_dscr, seq1, seq2);

        // mandar resultados
        result_msg->index_x = block_dscr->index_x;
        result_msg->index_y = block_dscr->index_y;
        extract_bottom_row(block_dscr, result_msg->data);
        extract_right_column(block_dscr, result_msg->data + BLOCK_WIDTH);
        extract_last_diagonal(block_dscr, result_msg->last_diag);

        MPI_Send(result_msg,
                 sizeof(BlockResultMessage),
                 MPI_BYTE,
                 slave_rank,
                 TAG_BLOCK_START,
                 MPI_COMM_WORLD);
    }
}