#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "primitives/primitives.h"
#include "primitives/list.h"

// matrix apunta al comienzo del bloque. Los seqs apuntan a las subsecuencias, limitadas por su length correspondiente
BlockResult *complete_block(int *matrix, MatrixCell *max_cell, CharArray *seq1, CharArray *seq2);

Direction calculate_traceback_block(char *matched_seq1, char *matched_seq2, int *matrix, MatrixCell *starting_cell, char *seq1, char *seq2);

// int max_val(int *matrix, int i, int j, char *seq1, char *seq2);

#endif