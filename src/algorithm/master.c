#include "algorithm/master.h"
#include <mpi.h>

void broadcast_sequences(int len1, int len2, char *seq1, char *seq2)
{
    MPI_Bcast(&len1, 1, MPI_INT, MASTER_RANK, MPI_COMM_WORLD);
    MPI_Bcast(&len2, 1, MPI_INT, MASTER_RANK, MPI_COMM_WORLD);

    MPI_Bcast(seq1, len1 + 1, MPI_CHAR, MASTER_RANK, MPI_COMM_WORLD);
    MPI_Bcast(seq2, len2 + 1, MPI_CHAR, MASTER_RANK, MPI_COMM_WORLD);
}

void load_start_message(BlockStartMessage *msg, int command, int index_x, int index_y,
                        int start_seq1, int start_seq2, int num_rows, int num_cols,
                        int *top_row, int *left_col, int prev_diag)
{
    msg->command = command;
    msg->index_x = index_x;
    msg->index_y = index_y;
    msg->start_seq1 = start_seq1;
    msg->start_seq2 = start_seq2;
    msg->num_rows = num_rows;
    msg->num_cols = num_cols;
    msg->prev_diag = prev_diag;
    // si es el mensaje de terminar, no hace falta copiar la fila superior ni la columna izquierda
    // mejorar eso tal vez
    if (command == 0)
    {

        memcpy(msg->data, top_row, BLOCK_WIDTH);                               // copio la fila superior a data[]
        memcpy(msg->data + BLOCK_WIDTH, left_col, BLOCK_HEIGHT * sizeof(int)); // copio la columna izquierda a data[BLOCK_WIDTH]
    }
}

void send_start_message(BlockStartMessage *msg)
{
    // en data se envia una fila completa y una columna completa, aunque no se usen el 100% de sus elementos,
    // para facilitar el envio MPI
    MPI_Send(msg, sizeof(BlockStartMessage), MPI_BYTE, dest, TAG_START_MESSAGE, MPI_COMM_WORLD);
}

void receive_result_message(BlockResultMessage *msg)
{
    MPI_Recv(*msg,
             sizeof(BlockResultMessage),
             MPI_BYTE,
             status.MPI_SOURCE,
             TAG_RESULT_MESSAGE,
             MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
}