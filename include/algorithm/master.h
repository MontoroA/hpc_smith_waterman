#include "blocks.h"

void master(int len1, int len2, char *seq1, char *seq2);

void load_BlockParam(BlockParam *msg, int id, int width, int height, char *seq1, char *seq2);

void send_BlockParam(BlockParam *msg, int dest);

void receive_BlockResult(BlockResult *msg, int *cnxt_pid, MPI_Status *status);