#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <mpi.h>

#include "hpc/mpi_handler.h"
#include "utils/io.h"
#include "utils/sequences.h"
#include "utils/utils.h"
#include "algorithm/blocks.h"
#include "algorithm/algorithm.h"
#include "algorithm/primitives/primitives.h"
#include "algorithm/primitives/queue.h"

#include "algorithm/master.h"
#include "algorithm/slave.h"

/*int run_master(int argc, char **argv)
{
    double start = MPI_Wtime();
    int mode = read_mode(argc, argv);
    if (mode == MODE_INVALID)
    {
        printf("Error leyendo modo: puede ser porque el modo fue incorrecto, o porque la cantidad de parámetros no fue especificada\n");
        return EXIT_FAILURE;
    }

    char **params = argv + 2;
    CharArray **seqs = execute_mode(mode, params);
    if (seqs == NULL)
    {
        return EXIT_SUCCESS;
    }
    CharArray *seq1 = seqs[0];
    CharArray *seq2 = seqs[1];

    int *matrix = malloc((1 + seq1->length) * (1 + seq2->length) * sizeof(int));

    BlockMap *map = create_block_map(seq1, seq2);
    Queue *queue = createQueue(max(seq1->length, seq2->length));

    int nro_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &nro_procs);
    bool *proc_available = malloc((nro_procs + 1) * sizeof(bool));
    for (int i = 1; i <= nro_procs; i++)
    {
        proc_available[i] = true;
    }

    // TODO: poner las filas dependientes para el primer bloque, antes de mandarselo al cnxt_pid = 1
    //  //put 0s in first row
    //  for(int j = 0; j < (1 + len2) ; j++){
    //      matrix[j] = 0;
    //  }
    //  //and first column
    //  for(int i = 0; i < (1 + len1) ; i++){
    //      matrix[i * (len2 + 1)] = 0;
    //  }

    int cnxt_pid = 1;
    char *data = NULL; // TODO Cargar con datos para enviar
    int count = 0;
    int tag = 0;
    MPI_Request request;
    MPI_Status status;
    int ierr = MPI_ISend(data, count, MPI_CHAR, cnxt_pid, tag, MPI_COMM_WORLD, request);
    int working_procs = 0;

    while (true)
    {
        ierr = MPI_Recv(data, count, MPI_CHAR, cnxt_pid, tag, MPI_COMM_WORLD, status);
        // obtener datos del MPI_Recv:
        BlockResult *result = (BlockResult *)data;
        // process result
        MatrixBlock **newly_available_blocks = update_map(result->block, map); // Se agrega info de la fila y columna del bloque procesado
        int iter = 0;
        while (newly_available_blocks[iter] != NULL)
        {
            enqueue(queue, *newly_available_blocks[iter]);
        }
        free(newly_available_blocks);
        proc_available[cnxt_pid] = true;
        working_procs--;

        for (int i = 1; i <= nro_procs; i++)
        {
            if (proc_available[i])
            {
                if (isEmpty(queue))
                    break;
                MatrixBlock block = dequeue(queue);
                MatrixBlock **required_neighbors = get_required_neighbors(block, map);
                BlockParam *param = create_blockParam(); // TODO
                MPI_ISend(&param, sizeof(MatrixBlock), MPI_BYTE, i, tag, MPI_COMM_WORLD);
                proc_available[i] = false;
                working_procs++;
                free(required_neighbors);
            }
        }

        if (isEmpty(queue) && working_procs == 0)
        {
            break;
        }
    }

    // traceback(matrix, res, seq1, seq2);
    // print_block_map(map, seq1, seq2);

    // send TAG_TERMINATE to all workers

    free(matrix);
    free(map);
    free(proc_available);
    free(queue);
    free(seq1->data);
    free(seq2->data);
    free(seq1);
    free(seq2);
    free(seqs);

    double end = MPI_Wtime();
    reports(start, end); // Recibe: tiempos, resultado algoritmo, metadata de ejecucion
    return EXIT_SUCCESS;
}*/

void run_master(int argc, char **argv)
{
    double start = MPI_Wtime();
    int mode = read_mode(argc, argv);
    if (mode == MODE_INVALID)
    {
        printf("Error leyendo modo: puede ser porque el modo fue incorrecto, o porque la cantidad de parámetros no fue especificada\n");
        return EXIT_FAILURE;
    }

    char **params = argv + 2;
    CharArray **seqs = execute_mode(mode, params);
    if (seqs == NULL)
    {
        return EXIT_SUCCESS;
    }
    CharArray *seq1 = seqs[0];
    CharArray *seq2 = seqs[1];

    // nueva funcion que representa al master
    master(seq1->length, seq2->length, seq1->data, seq2->data);

    free(seq1->data);
    free(seq2->data);
    free(seq1);
    free(seq2);
    free(seqs);

    double end = MPI_Wtime();
    reports(start, end); // Recibe: tiempos, resultado algoritmo, metadata de ejecucion
    return EXIT_SUCCESS;
}

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
    BlockStartMessage *start_msg = create_block_start_message();
    BlockResultMessage *result_msg = create_block_result_message();

    while (true)
    {
        // aca hay que poner la info para el cargar el mensaje de start, sacandola de lo que hiciste vos

        load_start_message(start_msg, /* command */ 0, /* index_x */ 0, /* index_y */ 0,
                           /* start_seq1 */ 0, /* start_seq2 */ 0, /* num_rows */ 0, /* num_cols */ 0,
                           /* top_row */ NULL, /* left_col */ NULL, /* prev_diag */ 0);

        send_start_message(start_msg);

        receive_result_message(result_msg); // BLOQUEANTE

        // procesar result_msg y actualizar mapa de bloques

        // ver si hay mas bloques

        // si no hay mas bloques, enviar mensaje de terminacion a todos los workers
    }

    // terminar slaves para que liberen su memoria y terminen
    for (int i = 0; i < nro_procs; i++)
    {
        load_start_message(start_msg, /* command */ 1, /* index_x */ 0, /* index_y */ 0,
                           /* start_seq1 */ 0, /* start_seq2 */ 0, /* num_rows */ 0, /* num_cols */ 0,
                           /* top_row */ NULL, /* left_col */ NULL, /* prev_diag */ 0);
        send_start_message(start_msg);
    }

    free(map);
    free(proc_available);
    free(queue);
}

// PROCESO SLAVE
void slave()
{
    work();
}