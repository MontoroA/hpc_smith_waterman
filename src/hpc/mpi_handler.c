#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <mpi.h>

#include "hpc/mpi_handler.h"
#include "utils/io.h"
#include "utils/sequences.h"
#include "utils/utils.h"
#include "algorithm/algorithm.h"
#include "algorithm/primitives/primitives.h"
#include "algorithm/primitives/queue.h"




int run_master(int argc, char** argv)
{
    double start = MPI_Wtime();
    int mode = read_mode(argc, argv);
    if(mode == MODE_INVALID){
        printf("Error leyendo modo: puede ser porque el modo fue incorrecto, o porque la cantidad de parámetros no fue especificada\n");
        return EXIT_FAILURE;
    }
    
    char** params = argv + 2;
    CharArray** seqs = execute_mode(mode, params);
    if(seqs == NULL){
        return EXIT_SUCCESS;
    }
    CharArray* seq1 = seqs[0];
    CharArray* seq2 = seqs[1];

    int* matrix = malloc((1 + seq1->length) * (1 + seq2->length) * sizeof(int));
    MatrixMap map = create_block_map(seq1, seq2);
    Queue* queue = createQueue(max(seq1->length, seq2->length));

    int nro_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &nro_procs);
    bool* proc_available = malloc((nro_procs + 1) * sizeof(bool));
    for(int i = 1; i <= nro_procs; i++){
        proc_available[i] = true;
    }
    int context_pid = 1; //elegir un primer proceso
    char* data = NULL; //Cargar con datos para enviar
    int count = 0;
    int tag = 0;
    MPI_Request request;
    MPI_Status status;
    int ierr =  MPI_ISend(data, count, MPI_CHAR, context_pid, tag, MPI_COMM_WORLD, request);
    int working_procs = 0;
    enqueue(queue, (MatrixIndex){0, 0});
    while(true){
        ierr = MPI_Recv(data, count, MPI_CHAR, context_pid, tag, MPI_COMM_WORLD, status);
        proc_available[context_pid] = true;
        MatrixIndex block; // Obtener de MPI_Recv
        // process result
        MatrixIndex* newly_available_blocks = get_unlocked_neighbors(block, map)
//         newly_available_blocks = get_unlocked_neighbors(block, map)
//         for each newly_available_block in newly_available_blocks: queue.enqueue(newly_available_block)
//         working_procs--;

        for(int i = 1; i <= nro_procs; i++){
            if(proc_available[i]){
                if(isEmpty(queue))
                    break;
                MatrixIndex block = dequeue(queue);
                // MPI_Send(block, sizeof(MatrixIndex), MPI_BYTE, i, TAG_BLOCK, MPI_COMM_WORLD);
                proc_available[i] = false;
                working_procs++;
            }
        }
//
//
//
        // for each available worker {
        //     if (queue has work) {
        //         dequeue next block
        //         send it to worker
        //         mark worker busy
        //         increment pending
        //     }
        // }

        if(isEmpty(queue) && working_procs == 0){
            break;
        }
    }
    // send TAG_TERMINATE to all workers
    
    // traceback(matrix, res, seq1, seq2);
    // print_block_map(map, seq1, seq2);

    free(matrix);
    free(map.visited);
    free(seq1->data);
    free(seq2->data);
    free(seq1);
    free(seq2);
    free(seqs);


    double end = MPI_Wtime();
    reports(start, end); //Recibe: tiempos, resultado algoritmo, metadata de ejecucion
    return EXIT_SUCCESS;
}

//TODO fix
void run_worker()
{
    while(true){
        // MPI_Status status;
        // int flag;
        // MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
        // if(flag){
        //     if(status.MPI_TAG == TAG_TERMINATE){
        //         break;
        //     }
            //Recibir bloque de datos y procesarlo
            // int* block_data;
            // MPI_Recv(block_data, block_size, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // Procesar bloque de datos
            // int* result = complete_block(block_data, seq1, seq2);
            // Enviar resultado al master
            // MPI_Send(result, result_size, MPI_INT, 0, TAG_RESULT, MPI_COMM_WORLD);
        // }
    }
    // MatrixCell* res = complete_block(matrix, seq1, seq2);
    // free(res);
}