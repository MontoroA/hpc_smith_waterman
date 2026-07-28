#ifndef MPI_HANDLER_H
#define MPI_HANDLER_H

#define BLOCK_HEIGHT 1000
#define BLOCK_WIDTH 1000

#define TAG_BLOCK_PARAM 0
#define TAG_BLOCK_RESULT 1
#define TAG_TERMINATE 2

#define MASTER_RANK 0

int run_master(int argc, char **argv);
int run_worker();

#endif