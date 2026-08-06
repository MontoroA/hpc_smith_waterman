#!/bin/sh
module load mpi/mpich-x86_64

export FI_PROVIDER=tcp

HOSTFILE=config/pcunix




make clean
make BLOCK_SIZE=500

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/500_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/500_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/500_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/500_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/500_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/500_6.txt)


make clean
make BLOCK_SIZE=1000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/1000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/1000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/1000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/1000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/1000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/1000_6.txt)



make clean
make BLOCK_SIZE=1500

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/1500_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/1500_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/1500_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/1500_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/1500_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/1500_6.txt)



make clean
make BLOCK_SIZE=2000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/2000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/2000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/2000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/2000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/2000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/2000_6.txt)


make clean
make BLOCK_SIZE=3000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/3000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/3000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/3000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/3000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/3000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/3000_6.txt)



make clean
make BLOCK_SIZE=4000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/4000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/4000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/4000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/4000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/4000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/4000_6.txt)











make clean
make BLOCK_SIZE=500

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/2k500_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/2k500_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/2k500_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/2k500_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/2k500_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/2k500_6.txt)


make clean
make BLOCK_SIZE=1000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k1000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k1000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k1000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k1000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k1000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k1000_6.txt)


make clean
make BLOCK_SIZE=1500

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/2k1500_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/2k1500_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/2k1500_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/2k1500_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/2k1500_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/2k1500_6.txt)

make clean
make BLOCK_SIZE=2000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k2000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k2000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k2000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k2000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k2000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k2000_6.txt)


make clean
make BLOCK_SIZE=3000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k3000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k3000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k3000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k3000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k3000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k3000_6.txt)



make clean
make BLOCK_SIZE=4000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k4000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k4000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k4000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k4000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k4000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k4000_6.txt)


