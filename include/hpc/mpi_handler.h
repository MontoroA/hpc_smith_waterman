#ifndef MPI_HANDLER_H
#define MPI_HANDLER_H

#define BLOCK_HEIGHT 10
#define BLOCK_WIDTH 10

#define TAG_BLOCK_PARAM 0
#define TAG_BLOCK_RESULT 1
#define TAG_TERMINATE 2
#define TAG_TRACEBACK_FIRST_RUN 3
#define TAG_TRACEBACK_RUN 4
#define TAG_TRACEBACK_NEIGHBOUR 5
#define TAG_TRACEBACK_RESULT 6
#define TAG_TRACEBACK_NEIGHBOUR_READY 7

#define MASTER_RANK 0

int run_master(int argc, char **argv);
int run_worker();

#endif