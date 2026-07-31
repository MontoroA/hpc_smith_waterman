#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "utils/cli.h"
#include "utils/sequences.h"
#include "utils/reports.h"
#include "runtime/mpi_handler.h"
#include "runtime/messages.h"

bool resume(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--resume") == 0)
        {
            return true;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1)
    {

        bool load_checkpoint = resume(argc, argv);
        int mode = read_mode(argc, argv, load_checkpoint);
        if (mode == MODE_INVALID)
        {
            logging(MASTER_RANK, "Error leyendo modo: puede ser porque el modo fue incorrecto, o porque la cantidad de parámetros no fue especificada\n");
            terminate_Workers();
            return EXIT_FAILURE;
        }

        char **params = argv + 2;
        SequenceBuffer **seqs = execute_mode(mode, params);
        if (seqs != NULL)
        {
            CharArray *seq1 = seqs[0]->data;
            CharArray *seq2 = seqs[1]->data;
            SWAReport *report = run_sequential(seq1, seq2, load_checkpoint);
            reports(report);
            free_SequenceBuffer(seqs[0]);
            free_SequenceBuffer(seqs[1]);
            free_Reports(report);
        }
        MPI_Finalize();
        return 0;
    }

    if (rank != MASTER_RANK)
    {
        run_worker();
    }
    else
    {
        bool load_checkpoint = resume(argc, argv);
        int mode = read_mode(argc, argv, load_checkpoint);
        if (mode == MODE_INVALID)
        {
            logging(MASTER_RANK, "Error leyendo modo: puede ser porque el modo fue incorrecto, o porque la cantidad de parámetros no fue especificada\n");
            terminate_Workers();
            return EXIT_FAILURE;
        }

        char **params = argv + 2;
        SequenceBuffer **seqs = execute_mode(mode, params);
        if (seqs != NULL)
        {
            CharArray *seq1 = seqs[0]->data;
            CharArray *seq2 = seqs[1]->data;
            SWAReport *report = run_master(seq1, seq2, load_checkpoint);
            reports(report);
            free_SequenceBuffer(seqs[0]);
            free_SequenceBuffer(seqs[1]);
            free_Reports(report);
        }
        terminate_Workers();
    }

    MPI_Finalize();
    return 0;
}