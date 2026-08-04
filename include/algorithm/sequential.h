#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H

#include "collections/arrays.h"
#include <stdbool.h>
#include "utils/reports.h"

SWAReport *sequential(CharArray *sequence1, CharArray *sequence2, bool load_checkpoint, double start_time, double *accumulated_time_checkpoint);

#endif