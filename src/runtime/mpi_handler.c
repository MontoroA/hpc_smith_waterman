#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "runtime/mpi_handler.h"
#include "utils/cli.h"
#include "utils/sequences.h"
#include "runtime/messages.h"
#include "utils/reports.h"
#include "algorithm/slave.h"
#include "algorithm/master.h"
#include "algorithm/sequential.h"

SWAReport *run_master(CharArray *seq1, CharArray *seq2, bool load_checkpoint)
{
    double start = MPI_Wtime();
    SWAReport *report = master(seq1, seq2, load_checkpoint);
    double end = MPI_Wtime();
    report->start_time = start;
    report->end_time = end;
    return report;
}

SWAReport *run_sequential(CharArray *seq1, CharArray *seq2, bool load_checkpoint)
{
    double start = MPI_Wtime();
    SWAReport *report = sequential(seq1, seq2, load_checkpoint);
    double end = MPI_Wtime();
    report->start_time = start;
    report->end_time = end;
    return report;
}

int run_worker()
{
    slave();
    return EXIT_SUCCESS;
}