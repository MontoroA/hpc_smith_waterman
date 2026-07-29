#ifndef MPI_HANDLER_H
#define MPI_HANDLER_H

#include "collections/arrays.h"
#include "utils/reports.h"
#include <stdbool.h>

#define MASTER_RANK 0
#define OTHERS_RANK 1

SWAReport *run_master(CharArray *seq1, CharArray *seq2, bool load_checkpoint);
int run_worker();

#endif