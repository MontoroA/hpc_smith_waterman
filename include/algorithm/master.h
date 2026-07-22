#include "blocks.h"

void master(int len1, int len2, char *seq1, char *seq2);

MatrixBlock *get_Block(BlockMap *map, int i, int j);

void load_BlockParam(BlockParam *msg, MatrixBlock *block, char *seq1, char *seq2);

void send_BlockParam(BlockParam *msg, int dest);

void receive_BlockResult(BlockResult *msg, int *cnxt_pid, MPI_Status *status);

void enqueue_newBlocks(Queue *queue, BlockMap *map, MatrixBlock *block);