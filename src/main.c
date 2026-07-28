#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "utils/cli.h"
#include "utils/sequences.h"
#include "runtime/mpi_handler.h"


int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == MASTER_RANK)
        run_master(argc, argv);
    else
        run_worker();

    MPI_Finalize();
    return 0;
}