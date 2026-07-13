#!/bin/sh

. config/MPI_PARAMS.conf

mpiexec -np $NRO_PROCS -hostfile $HOSTFILE ./build/smith_waterman "$@"