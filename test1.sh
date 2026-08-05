#!/bin/sh
module load mpi/mpich-x86_64

export FI_PROVIDER=tcp

HOSTFILE=config/pcunix

make clean
make BLOCK_SIZE=5000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/5000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/5000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/5000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/5000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/5000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/5000_6.txt)


make clean
make BLOCK_SIZE=7500

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/7500_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/7500_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/7500_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/7500_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/7500_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/7500_6.txt)


make clean
make BLOCK_SIZE=10000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/10000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/10000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/10000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/10000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/10000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/10000_6.txt)



make clean
make BLOCK_SIZE=15000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/15000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/15000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/15000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/15000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/15000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/15000_6.txt)




make clean
make BLOCK_SIZE=20000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/100k_10000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/100k_10000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/100k_10000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/100k_10000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/100k_10000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/100k_10000_6.txt)




make clean
make BLOCK_SIZE=25000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/100k_15000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/100k_15000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/100k_15000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/100k_15000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/100k_15000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/100k_15000_6.txt)



make clean
make BLOCK_SIZE=30000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/100k_20000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/100k_20000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/100k_20000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/100k_20000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/100k_20000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/100k_20000_6.txt)


make clean
make BLOCK_SIZE=35000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/100k_25000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/100k_25000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/100k_25000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/100k_25000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/100k_25000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/100k_25000_6.txt)


make clean
make BLOCK_SIZE=40000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/40000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/40000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/40000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/40000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/40000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/40000_6.txt)


make clean
make BLOCK_SIZE=45000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/45000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/45000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/45000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/45000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/45000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/45000_6.txt)



make clean
make BLOCK_SIZE=50000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/50000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/50000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/50000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/50000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 | tee >(tail -n 1 > ./output_cli/50000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/100k_1 ./data/large/100k_2 --resume | tee >(tail -n 1 > ./output_cli/50000_6.txt)























make clean
make BLOCK_SIZE=5000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k5000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k5000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k5000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k5000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k5000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k5000_6.txt)


make clean
make BLOCK_SIZE=7500

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k7500_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k7500_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k7500_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k7500_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k7500_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k7500_6.txt)


make clean
make BLOCK_SIZE=10000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k10000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k10000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k10000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k10000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k10000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k10000_6.txt)



make clean
make BLOCK_SIZE=15000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k15000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k15000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k15000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k15000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k15000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k15000_6.txt)




make clean
make BLOCK_SIZE=20000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k200k_10000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k200k_10000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k200k_10000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k200k_10000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k200k_10000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k200k_10000_6.txt)




make clean
make BLOCK_SIZE=25000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k200k_15000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k200k_15000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k200k_15000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k200k_15000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k200k_15000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k200k_15000_6.txt)



make clean
make BLOCK_SIZE=30000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k200k_20000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k200k_20000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k200k_20000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k200k_20000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k200k_20000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k200k_20000_6.txt)


make clean
make BLOCK_SIZE=35000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k200k_25000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k200k_25000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k200k_25000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k200k_25000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k200k_25000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k200k_25000_6.txt)


make clean
make BLOCK_SIZE=40000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k40000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k40000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k40000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k40000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k40000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k40000_6.txt)


make clean
make BLOCK_SIZE=45000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k45000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k45000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k45000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k45000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k45000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k45000_6.txt)



make clean
make BLOCK_SIZE=50000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k50000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k50000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k50000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k50000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 | tee >(tail -n 1 > ./output_cli/2k50000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/200k_1 ./data/large/200k_2 --resume | tee >(tail -n 1 > ./output_cli/2k50000_6.txt)