#include <mpi.h>

#include "algorithm/master.h"
#include "algorithm/blocks.h"
#include "algorithm/algorithm.h"
#include "algorithm/primitives/primitives.h"
#include "algorithm/primitives/queue.h"


// PROCESO MASTER
void master(int len1, int len2, char *seq1, char *seq2)
{
    broadcast_sequences(len1, len2, seq1, seq2);

    // preparar sus estructuras de control, mapa de bloques, etc
    BlockMap *map = create_block_map(seq1, seq2);
    Queue *queue = createQueue(max(seq1->length, seq2->length));

    int nro_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &nro_procs);
    bool *proc_available = malloc((nro_procs + 1) * sizeof(bool));
    for (int i = 1; i <= nro_procs; i++)
    {
        proc_available[i] = true;
    }

    // solo se necesita 1 de cada para trabajar el master
    BlockParam* param_msg = create_blockParam();
    BlockResult *result_msg = create_blockResult();

    for(int j = 0; j < (1 + len2) ; j++){
        param_msg->block.last_matrix_row[j] = 0;
    }
    //and first column
    for(int i = 0; i < (1 + len1) ; i++){
        param_msg->block.last_matrix_col[i] = 0;
    }


    int cnxt_pid = 1;
    load_BlockParam(param_msg, get_MatrixBlock(0, 0, map), 0, len1, len2, seq1, seq2);

    int count = 0;
    int tag = 0;
    MPI_Request request;
    MPI_Status status;
    int ierr =  MPI_ISend(param_msg, count, MPI_BYTE, cnxt_pid, tag, MPI_COMM_WORLD, request);
    int working_procs = 1;

    while (true)
    {
        receive_BlockResult(result_msg, &cnxt_pid, &tag, &status);
        // process result
        MatrixBlock** newly_available_blocks = update_BlockMap(result_msg->block, map); 
        int iter = 0;
        while(newly_available_blocks[iter] != NULL){
            enqueue(queue, *newly_available_blocks[iter]); 
        }
        free(newly_available_blocks);
        proc_available[cnxt_pid] = true;
        working_procs--;


        for(int i = 1; i <= nro_procs; i++){
            if(proc_available[i]){
                if(isEmpty(queue))
                    break;
                MatrixBlock* block = dequeue(queue);
                load_dependencies(block, map);
                load_BlockParam(param_msg, block, 0, len1, len2, seq1, seq2); //TODO
                send_BlockParam(param_msg, i);
                proc_available[i] = false;
                working_procs++;
            }
        }

        if(isEmpty(queue) && working_procs == 0){
            break;
        }

    }

    // traceback(matrix, res, seq1, seq2);
    // print_block_map(map, seq1, seq2);

    // terminar slaves para que liberen su memoria y terminen
    for (int i = 0; i < nro_procs; i++)
    {
        // send TAG_TERMINATE to all workers

        //Avisar a los workers que terminen, para que liberen su memoria y finalizen
        load_start_message(start_msg, /* command */ 1, /* index_x */ 0, /* index_y */ 0,
                           /* start_seq1 */ 0, /* start_seq2 */ 0, /* num_rows */ 0, /* num_cols */ 0,
                           /* top_row */ NULL, /* left_col */ NULL, /* prev_diag */ 0);
        send_BlockParam(start_msg, i);
    }

    free(map);
    free(proc_available);
    free(queue);
}

// void broadcast_sequences(int len1, int len2, char *seq1, char *seq2)
// {
//     MPI_Bcast(&len1, 1, MPI_INT, MASTER_RANK, MPI_COMM_WORLD);
//     MPI_Bcast(&len2, 1, MPI_INT, MASTER_RANK, MPI_COMM_WORLD);

//     MPI_Bcast(seq1, len1 + 1, MPI_CHAR, MASTER_RANK, MPI_COMM_WORLD);
//     MPI_Bcast(seq2, len2 + 1, MPI_CHAR, MASTER_RANK, MPI_COMM_WORLD);
// }

void load_BlockParam(BlockParam *msg, MatrixBlock* block, int id, int width, int height, char *seq1, char *seq2)
{
    msg->id = id;
    msg->width = width;
    msg->height = height;
    memcpy(msg->seq1, seq1, width * sizeof(char));
    memcpy(msg->seq2, seq2, height * sizeof(char));
}
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

void send_BlockParam(BlockParam *msg, int dest)
{
    MPI_Send(msg, sizeof(BlockParam), MPI_BYTE, dest, TAG_START_MESSAGE, MPI_COMM_WORLD);
}

void receive_BlockResult(BlockResult *msg, int* cnxt_pid, int tag, MPI_Status *status)
{
    char* buffer; //TODO se puede poner msg nomas en la primitiva de recv?
    MPI_Recv(buffer, sizeof(BlockResult), MPI_BYTE, cnxt_pid, tag, MPI_COMM_WORLD, status);
    msg = (BlockResult*) buffer;
}