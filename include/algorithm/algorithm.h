#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "blocks.h"
#include "primitives.h"

#include "collections/list.h"
#include "collections/arrays.h"

void print_matrix(int *matrix, CharArray *sequence1, CharArray *sequence2);

void complete_block(int *matrix, MatrixCell *max_cell, CharArray *seq1, CharArray *seq2);

Direction calculate_traceback_block(char *matched_seq1, char *matched_seq2, int *matrix, MatrixCell *starting_cell, int *traceback_length, char *seq1, char *seq2);

#endif