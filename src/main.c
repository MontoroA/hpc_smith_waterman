#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "utils/io.h"
#include "utils/sequences.h"
#include "hpc/mpi_handler.h"
#include "algorithm/algorithm.h"


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