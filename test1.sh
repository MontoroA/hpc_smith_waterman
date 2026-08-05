#!/bin/sh
module load mpi/mpich-x86_64

export FI_PROVIDER=tcp

HOSTFILE=config/pcunix

make clean
make BLOCK_SIZE=5000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/5000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/5000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/5000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/5000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/5000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/5000_6.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/5000_7.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/5000_8.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/5000_9.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/5000_10.txt)


make clean
make BLOCK_SIZE=7500

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/7500_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/7500_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/7500_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/7500_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/7500_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/7500_6.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/7500_7.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/7500_8.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/7500_9.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/7500_10.txt)


make clean
make BLOCK_SIZE=10000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/10000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/10000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/10000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/10000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/10000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/10000_6.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/10000_7.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/10000_8.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/10000_9.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/10000_10.txt)



make clean
make BLOCK_SIZE=15000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/15000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/15000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/15000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/15000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/15000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/15000_6.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/15000_7.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/15000_8.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/15000_9.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/15000_10.txt)




make clean
make BLOCK_SIZE=20000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/20000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/20000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/20000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/20000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/20000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/20000_6.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/20000_7.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/20000_8.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/20000_9.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/20000_10.txt)




make clean
make BLOCK_SIZE=25000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/25000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/25000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/25000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/25000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/25000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/25000_6.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/25000_7.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/25000_8.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/25000_9.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/25000_10.txt)



make clean
make BLOCK_SIZE=30000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/30000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/30000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/30000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/30000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/30000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/30000_6.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/30000_7.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/30000_8.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/30000_9.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/30000_10.txt)


make clean
make BLOCK_SIZE=35000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/35000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/35000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/35000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/35000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/35000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/35000_6.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/35000_7.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/35000_8.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/35000_9.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/35000_10.txt)


make clean
make BLOCK_SIZE=40000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/40000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/40000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/40000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/40000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/40000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/40000_6.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/40000_7.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/40000_8.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/40000_9.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/40000_10.txt)


make clean
make BLOCK_SIZE=45000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/45000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/45000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/45000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/45000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/45000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/45000_6.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/45000_7.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/45000_8.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/45000_9.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/45000_10.txt)



make clean
make BLOCK_SIZE=50000

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/50000_1.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/50000_2.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/50000_3.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/50000_4.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/50000_5.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/50000_6.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/50000_7.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/50000_8.txt)

mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tee >(tail -n 1 > ./output_cli/50000_9.txt)
mpiexec -np 10 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tee >(tail -n 1 > ./output_cli/50000_10.txt)