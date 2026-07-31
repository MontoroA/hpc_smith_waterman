#!/bin/sh

. config/MPI_PARAMS.conf

NRO_PROCS=8

mpiexec -np $NRO_PROCS -hostfile $HOSTFILE ./build/smith_waterman "$@"