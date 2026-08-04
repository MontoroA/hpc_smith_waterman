export FI_PROVIDER=tcp

HOSTFILE=config/pcunix

make clean
make BLOCK_SIZE=2500

mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9



make clean
make BLOCK_SIZE=5000

mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9








make clean
make BLOCK_SIZE=7500

mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9






make clean
make BLOCK_SIZE=10000

mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9










make clean
make BLOCK_SIZE=12000

mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/8 ./data/large/9

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/8 ./data/large/9

