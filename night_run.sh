#!/bin/sh
export FI_PROVIDER=tcp

HOSTFILE=config/pcunix

make clean
make BLOCK_SIZE=1000

# SEQUENCIAS DE TAMANIO 10 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3



# SEQUENCIAS DE TAMANIO 100 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5



# SEQUENCIAS DE TAMANIO 1 000 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7







########################################################################################################################################################################################################################
########################################################################################################################################################################################################################
########################################################################################################################################################################################################################


make clean
make BLOCK_SIZE=2500


# SEQUENCIAS DE TAMANIO 10 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3



# SEQUENCIAS DE TAMANIO 100 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5



# SEQUENCIAS DE TAMANIO 1 000 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7







########################################################################################################################################################################################################################
########################################################################################################################################################################################################################
########################################################################################################################################################################################################################




make clean
make BLOCK_SIZE=5000



# SEQUENCIAS DE TAMANIO 10 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3



# SEQUENCIAS DE TAMANIO 100 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5



# SEQUENCIAS DE TAMANIO 1 000 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7



########################################################################################################################################################################################################################
########################################################################################################################################################################################################################
########################################################################################################################################################################################################################



make clean
make BLOCK_SIZE=7500


# SEQUENCIAS DE TAMANIO 10 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3



# SEQUENCIAS DE TAMANIO 100 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5



# SEQUENCIAS DE TAMANIO 1 000 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7






########################################################################################################################################################################################################################
########################################################################################################################################################################################################################
########################################################################################################################################################################################################################






make clean
make BLOCK_SIZE=10000


# SEQUENCIAS DE TAMANIO 10 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3



# SEQUENCIAS DE TAMANIO 100 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5



# SEQUENCIAS DE TAMANIO 1 000 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7
