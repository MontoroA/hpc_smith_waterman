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





    BlockMap* map = create_block_map(seq1, seq2);
    Queue* queue = createQueue(max(seq1->length, seq2->length));

    int nro_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &nro_procs);
    bool* proc_available = malloc((nro_procs + 1) * sizeof(bool));
    for(int i = 1; i <= nro_procs; i++){
        proc_available[i] = true;
    }


    //TODO: poner las filas dependientes para el primer bloque, antes de mandarselo al cnxt_pid = 1
    // //put 0s in first row 
    // for(int j = 0; j < (1 + len2) ; j++){
    //     matrix[j] = 0;
    // }
    // //and first column
    // for(int i = 0; i < (1 + len1) ; i++){
    //     matrix[i * (len2 + 1)] = 0;
    // }


    int cnxt_pid = 1;
    char* data = NULL; //TODO Cargar con datos para enviar
    int count = 0;
    int tag = 0;
    MPI_Request request;
    MPI_Status status;
    int ierr =  MPI_ISend(data, count, MPI_CHAR, cnxt_pid, tag, MPI_COMM_WORLD, request);
    int working_procs = 0;

    while(true){
        ierr = MPI_Recv(data, count, MPI_CHAR, cnxt_pid, tag, MPI_COMM_WORLD, status);
        //obtener datos del MPI_Recv:
        BlockResult* result = (BlockResult*) data; 
        // process result
        MatrixBlock** newly_available_blocks = update_map(result->block, map); //Se agrega info de la fila y columna del bloque procesado
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
                MatrixBlock block = dequeue(queue);
                MatrixBlock** required_neighbors = get_required_neighbors(block, map);
                BlockParam* param = create_blockParam(); //TODO
                MPI_ISend(&param, sizeof(MatrixBlock), MPI_BYTE, i, tag, MPI_COMM_WORLD); 
                proc_available[i] = false;
                working_procs++;
                free(required_neighbors);
            }
        }

        if(isEmpty(queue) && working_procs == 0){
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
    reports(start, end); //Recibe: tiempos, resultado algoritmo, metadata de ejecucion
    return EXIT_SUCCESS;
}

void run_worker()
{
    MPI_Status status;
    int flag;
    int tag;
    int size;
    void* msg;
    int type;
    int cnxt_pid;
    while(true){
        MPI_Recv(&msg, size, type, cnxt_pid, tag, MPI_COMM_WORLD, &status);
        if(status.MPI_TAG == TAG_TERMINATE){
            break;
        }
        BlockParam* param = (BlockParam*) msg;
        int* matrix = malloc(param->width * param->height * sizeof(int));
        load_block(matrix, param);
        CharArray* seq1 = malloc(sizeof(CharArray));
        seq1->data = param->seq1;
        seq1->length = param->width;
        CharArray* seq2 = malloc(sizeof(CharArray));
        seq2->data = param->seq2;
        seq2->length = param->height;
        int* result = complete_block(matrix, seq1, seq2);

        //TODO al ser asincronico, deberia llamar alguna primitiva antes que chequee si ya se libero el buffer para hacer esto
        BlockResult* block_result = malloc(sizeof(BlockResult));
        extract_bottom_row(matrix, block_result);
        extract_right_column(matrix, block_result);
        MPI_Request request;
        MPI_ISend(block_result, sizeof(BlockResult), MPI_BYTE, MASTER_RANK, tag, MPI_COMM_WORLD, request);
        free(matrix);
        free(seq1);
        free(seq2);
    }
    // MatrixCell* res = complete_block(matrix, seq1, seq2);
    // free(res);
}