#ifndef MESSAGES_H
#define MESSAGES_H

#include "algorithm/blocks.h"
// #include "runtime/mpi_handler.h"

#define TAG_BLOCK_PARAM 0
#define TAG_BLOCK_RESULT 1
#define TAG_TERMINATE 2
#define TAG_TRACEBACK_RUN 3
#define TAG_TRACEBACK_RESULT 4

void send_BlockParam(BlockParam *msg, int dest, int tag);
void receive_BlockResult(BlockResult *msg, MPI_Status *status);
void receive_TracebackResult(TracebackResult *msg, int *cnxt_pid, MPI_Status *status);
void send_TracebackResult(TracebackResult *msg, int tag);
void send_BlockResult(BlockResult *msg);
void receive_BlockParam(BlockParam *msg, MPI_Status *status);
void terminate_Workers();

#endif