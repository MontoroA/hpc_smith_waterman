#!/bin/sh

#NRO_PROCS: Cantidad de esclavos
NRO_PROCS=8
#Archivo de hosts a usar para la ejecución.
HOSTFILE=config/hosts_local

export FI_PROVIDER=tcp

# MODE="$1"
# SEQ1="$2"
# SEQ2="$3"

# SIZE1=$(wc -c < "$SEQ1")
# SIZE2=$(wc -c < "$SEQ2")
# MATRIX_SIZE=$((SIZE1 * SIZE2))

# if [ "$MATRIX_SIZE" -lt 100000 ]; then
#     NRO_PROCS=2
# elif [ "$MATRIX_SIZE" -lt 10000000 ]; then
#     NRO_PROCS=4
# elif [ "$MATRIX_SIZE" -lt 1000000000 ]; then
#     NRO_PROCS=8
# else
#     NRO_PROCS=16
# fi

mpiexec -np $NRO_PROCS -hostfile $HOSTFILE ./build/smith_waterman "$@"
