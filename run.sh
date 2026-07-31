#!/bin/sh

. config/MPI_PARAMS.conf

export FI_PROVIDER=tcp

#parallel
#mpiexec -np $NRO_PROCS -hostfile $HOSTFILE ./build/smith_waterman "$@"
#sequential
mpiexec -np 1 ./build/smith_waterman "$@"