#ifndef MPI_HANDLER_H
#define MPI_HANDLER_H

#define BLOCK_HEIGHT 10000
#define BLOCK_WIDTH 10000

static const int MASTER_RANK = 0;

int run_master(int argc, char** argv);
void run_worker();

#endif