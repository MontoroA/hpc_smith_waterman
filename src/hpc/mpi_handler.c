#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#include "hpc/mpi_handler.h"
#include "utils/io.h"
#include "utils/sequences.h"
#include "utils/utils.h"
#include "algorithm/algorithm.h"
#include "algorithm/primitives/primitives.h"

int run_master(int argc, char** argv)
{
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

    double start = MPI_Wtime();
    int* matrix = malloc((1 + seq1->length) * (1 + seq2->length) * sizeof(int));
    MatrixCell* res = complete_block(matrix, seq1, seq2);
    traceback(matrix, res, seq1, seq2);
    double end = MPI_Wtime();
    
    //Recibe: tiempos, resultado algoritmo, metadata de ejecucion
    reports(start, end);

    free(matrix);
    free(seq1->data);
    free(seq2->data);
    free(seq1);
    free(seq2);
    free(seqs);
    free(res);
    return EXIT_SUCCESS;
}


void run_worker()
{
    // Implementación del código del trabajador
}