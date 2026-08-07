#ifndef MASTER_H
#define MASTER_H

#include <stdbool.h>

#include "collections/arrays.h"
#include "utils/reports.h"

SWAReport *master(CharArray *seq1, CharArray *seq2, bool load_checkpoint, double start_time, double *accumulated_time_checkpoint);

#endif