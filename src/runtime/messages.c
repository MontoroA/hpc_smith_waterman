#include <mpi.h>

#include "runtime/messages.h"


void send_BlockParam(BlockParam *msg, int dest, int tag)
{
    MPI_Send(msg, sizeof(BlockParam), MPI_BYTE, dest, tag, MPI_COMM_WORLD);
}

void receive_BlockResult(BlockResult *msg, MPI_Status *status)
{
    MPI_Recv(msg, sizeof(BlockResult), MPI_BYTE, MPI_ANY_SOURCE, TAG_BLOCK_RESULT, MPI_COMM_WORLD, status);
}

void receive_TracebackResult(TracebackResult *msg, int *cnxt_pid, MPI_Status *status)
{
    MPI_Recv(msg, sizeof(TracebackResult), MPI_BYTE, *cnxt_pid, TAG_TRACEBACK_RESULT, MPI_COMM_WORLD, status);
}

void send_TracebackResult(TracebackResult *msg, int tag)
{
    MPI_Send(msg, sizeof(TracebackResult), MPI_BYTE, MASTER_RANK, tag, MPI_COMM_WORLD);
}

void send_BlockResult(BlockResult *msg)
{
    MPI_Send(msg, sizeof(BlockResult), MPI_BYTE, MASTER_RANK, TAG_BLOCK_RESULT, MPI_COMM_WORLD);
}

void receive_BlockParam(BlockParam *msg, MPI_Status *status)
{
    MPI_Recv(msg,
             sizeof(BlockParam),
             MPI_BYTE,
             MASTER_RANK,
             MPI_ANY_TAG,
             MPI_COMM_WORLD,
             status);
}


void terminate_Workers()
{
    int nro_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &nro_procs);
    for(int i = 1; i < nro_procs; i++)
    {
        MPI_Send(NULL, 0, MPI_BYTE, i, TAG_TERMINATE, MPI_COMM_WORLD);
    }
}