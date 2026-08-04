#!/bin/sh
module load mpi/mpich-x86_64

export FI_PROVIDER=tcp

HOSTFILE=config/pcunix

make clean
make BLOCK_SIZE=2500

mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/1.txt)
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/2.txt)

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/3.txt)
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/4.txt)

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/5.txt)
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/6.txt)

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/7.txt)
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/8.txt)

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/9.txt)
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/10.txt)

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/11.txt)
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/12.txt)


make clean
make BLOCK_SIZE=5000

mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/13.txt)
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/14.txt)

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/15.txt)
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/16.txt)

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/17.txt)
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/18.txt)

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/19.txt)
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/20.txt)

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/21.txt)
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/22.txt)

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/23.txt)
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/24.txt)


make clean
make BLOCK_SIZE=7500

mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/25.txt)
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/26.txt)

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/27.txt)
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/28.txt)

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/29.txt)
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/30.txt)

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/31.txt)
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/32.txt)

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/33.txt)
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/34.txt)

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/35.txt)
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/36.txt)


make clean
make BLOCK_SIZE=10000

mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/37.txt)
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/38.txt)

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/39.txt)
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/40.txt)

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/41.txt)
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/42.txt)

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/43.txt)
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/44.txt)

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/45.txt)
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/46.txt)

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/47.txt)
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/48.txt)


make clean
make BLOCK_SIZE=12000

mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/49.txt)
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/50.txt)

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/51.txt)
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/52.txt)

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/53.txt)
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/54.txt)

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/55.txt)
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/56.txt)

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/57.txt)
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/58.txt)

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9 | tee >(tail -n 1 > ./output_cli/heavy/59.txt)
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9 --resume | tee >(tail -n 1 > ./output_cli/heavy/60.txt)

