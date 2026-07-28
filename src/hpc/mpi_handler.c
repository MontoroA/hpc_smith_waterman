#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <mpi.h>

#include "hpc/mpi_handler.h"
#include "utils/io.h"
#include "utils/sequences.h"
#include "utils/utils.h"
#include "utils/reports.h"

#include "algorithm/master.h"
#include "algorithm/slave.h"


int run_master(int argc, char **argv)
{
    double start = MPI_Wtime();
    int mode = read_mode(argc, argv);
    if (mode == MODE_INVALID)
    {
        print(MASTER_RANK, "Error leyendo modo: puede ser porque el modo fue incorrecto, o porque la cantidad de parámetros no fue especificada\n");
        return EXIT_FAILURE;
    }

    char **params = argv + 2;
    CharArray **seqs = execute_mode(mode, params);
    if (seqs == NULL)
    {
        print(MASTER_RANK, "Error ejecutando modo: no se pudieron cargar las secuencias\n");
        return EXIT_SUCCESS;
    }
    CharArray *seq1 = seqs[0];
    CharArray *seq2 = seqs[1];

    // nueva funcion que representa al master
    master(seq1, seq2);
    free(seq1->data);
    free(seq2->data);
    free(seq1);
    free(seq2);
    free(seqs);

    double end = MPI_Wtime();
    reports(start, end); // Recibe: tiempos, resultado algoritmo, metadata de ejecucion
    return EXIT_SUCCESS;
}

// PROCESO SLAVE
int run_worker()
{
    slave();
    return EXIT_SUCCESS;
}