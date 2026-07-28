#ifndef MPI_HANDLER_H
#define MPI_HANDLER_H

#define MASTER_RANK 0
#define OTHERS_RANK 1

int run_master(int argc, char **argv);
int run_worker();

#endif