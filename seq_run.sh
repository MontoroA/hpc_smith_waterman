#!/bin/sh

HOSTFILE=config/hosts_local

export FI_PROVIDER=tcp

mpiexec -np 1 ./build/smith_waterman "$@"
