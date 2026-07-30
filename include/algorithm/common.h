#ifndef COMMON_H
#define COMMON_H

#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>

#include "algorithm/blocks.h"
#include "algorithm/algorithm.h"
#include "collections/queue.h"
#include "runtime/messages.h"
#include "runtime/checkpoint.h"

extern CharArray *seq1;
extern CharArray *seq2;
extern BlockMap *map;
extern Queue *queue;
extern bool *proc_available;
extern BlockResult *result_msg;
extern BlockParam *param_msg;
extern MatrixBlock *block;
extern int nro_procs;
extern int cnxt_pid;
extern int working_procs;
extern MPI_Status status;
extern MatrixBlock *max_score_block;
extern TracebackResult *traceback_msg;
extern FILE *checkpoint;
extern int wavefront_number;
extern List *matched_seq1;
extern List *matched_seq2;
extern int *matrix;
extern MatrixCell *cell;

void enqueue_ready_blocks(Queue *queue, BlockMap *map, MatrixBlock *block);
void update_Traceback(TracebackResult *traceback_msg, List **matched_seq1, List **matched_seq2);
MatrixBlock *get_NextBlockTraceback(BlockMap *map, TracebackResult *traceback_msg);
void load_NextStartingCell(TracebackResult *traceback_msg, MatrixBlock *block);

#endif