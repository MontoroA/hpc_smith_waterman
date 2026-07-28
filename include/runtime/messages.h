#ifndef MESSAGES_H
#define MESSAGES_H

#include "runtime/mpi_handler.h"
#include "algorithm/blocks.h"

void send_BlockParam(BlockParam *msg, int dest, int tag);
void receive_BlockResult(BlockResult *msg, MPI_Status *status);
void receive_TracebackResult(TracebackResult *msg, int *cnxt_pid, MPI_Status *status);
void send_TracebackResult(TracebackResult *msg, int tag);
void send_BlockResult(BlockResult *msg);
void receive_BlockParam(BlockParam *msg, MPI_Status *status);

#endif