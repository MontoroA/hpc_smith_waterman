#ifndef MASTER_H
#define MASTER_H

#include "algorithm/blocks.h"
#include "algorithm/primitives/queue.h"

void master(CharArray *seq1, CharArray *seq2);

// void load_BlockParam(BlockParam *msg, MatrixBlock *block, CharArray *seq1, CharArray *seq2);

// void send_BlockParam(BlockParam *msg, int dest);

void receive_BlockResult(BlockResult *msg, int *cnxt_pid, MPI_Status *status);

void enqueue_newBlocks(Queue *queue, BlockMap *map, MatrixBlock *block);

#endif