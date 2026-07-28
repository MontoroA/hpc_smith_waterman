// #include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "runtime/mpi_handler.h"
#include "utils/cli.h"
#include "utils/sequences.h"
#include "runtime/messages.h"
#include "utils/reports.h"

#include "algorithm/slave.h"
#include "algorithm/master.h"

int run_master(int argc, char **argv)
{
    int mode = read_mode(argc, argv);
    if (mode == MODE_INVALID)
    {
        logging(MASTER_RANK, "Error leyendo modo: puede ser porque el modo fue incorrecto, o porque la cantidad de parámetros no fue especificada\n");
        return EXIT_FAILURE;
    }

    char **params = argv + 2;
    CharArray **seqs = execute_mode(mode, params);
    if (seqs != NULL)
    {
        double start = MPI_Wtime();
        CharArray *seq1 = seqs[0];
        CharArray *seq2 = seqs[1];
        bool load_checkpoint = false; // TODO add cli option to load checkpoint from start

        master(seq1, seq2, load_checkpoint);

        free(seq1->data);
        free(seq2->data);
        free(seq1);
        free(seq2);
        free(seqs);
        double end = MPI_Wtime();
        reports(start, end); // Recibe: tiempos, resultado algoritmo, metadata de ejecucion
    }
    terminate_Workers();
    return EXIT_SUCCESS;
}

int run_worker()
{
    slave();
    return EXIT_SUCCESS;
}