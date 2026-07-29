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



SWAReport* run_master(CharArray* seq1, CharArray* seq2)
{
    SWAReport* report = malloc(sizeof(SWAReport));
    double start = MPI_Wtime();
    master(seq1, seq2);
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