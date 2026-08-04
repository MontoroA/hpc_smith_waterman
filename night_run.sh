#!/bin/sh
export FI_PROVIDER=tcp

HOSTFILE=config/pcunix

make clean
make BLOCK_SIZE=1000

# SEQUENCIAS DE TAMANIO 10 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/1.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/2.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/3.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/4.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/5.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/6.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/7.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/8.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/9.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/10.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/11.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/12.txt

# SEQUENCIAS DE TAMANIO 100 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/13.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/14.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/16.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/17.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/18.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/19.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/20.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/21.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/22.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/23.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/24.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/25.txt

# SEQUENCIAS DE TAMANIO 1 000 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/26.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/27.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/28.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/29.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/30.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/31.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/32.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/33.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/34.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/35.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/36.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/36-.txt

###########################################################################################################################
###########################################################################################################################
###########################################################################################################################

make clean
make BLOCK_SIZE=2500

# SEQUENCIAS DE TAMANIO 10 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/37.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/38.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/39.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/40.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/41.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/42.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/43.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/44.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/45.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/46.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/47.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/48.txt

# SEQUENCIAS DE TAMANIO 100 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/49.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/50.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/51.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/52.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/53.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/54.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/55.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/56.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/57.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/58.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/59.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/60.txt

# SEQUENCIAS DE TAMANIO 1 000 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/61.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/62.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/63.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/64.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/65.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/66.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/67.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/68.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/69.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/70.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/71.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/71-.txt

###########################################################################################################################
###########################################################################################################################
###########################################################################################################################

make clean
make BLOCK_SIZE=5000

# SEQUENCIAS DE TAMANIO 10 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/72.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/73.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/74.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/75.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/76.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/77.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/78.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/79.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/80.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/81.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/82.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/83.txt

# SEQUENCIAS DE TAMANIO 100 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/84.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/85.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/86.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/87.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/88.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/89.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/90.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/91.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/92.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/93.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/94.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/95.txt

# SEQUENCIAS DE TAMANIO 1 000 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/96.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/97.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/98.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/99.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/100.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/101.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/102.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/103.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/104.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/105.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/106.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume| tail -n 1 > /output_cli/106-.txt

############################################################################################################################
############################################################################################################################
############################################################################################################################

make clean
make BLOCK_SIZE=7500

# SEQUENCIAS DE TAMANIO 10 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/107.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/108.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/109.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/110.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/111.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/112.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/113.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/114.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/115.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/116.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/117.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/118.txt

# SEQUENCIAS DE TAMANIO 100 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/119.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/120.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/121.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/122.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/123.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/124.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/125.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/126.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/127.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/128.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/129.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/130.txt

# SEQUENCIAS DE TAMANIO 1 000 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/131.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/132.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/133.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/134.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/135.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/136.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/137.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/138.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/139.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/140.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/141.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/141-.txt

############################################################################################################################
############################################################################################################################
############################################################################################################################

make clean
make BLOCK_SIZE=10000

# SEQUENCIAS DE TAMANIO 10 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/142.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/143.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/144.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/145.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/146.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/147.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/148.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/149.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/150.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/151.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3 | tail -n 1 > /output_cli/152.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/2 ./data/large/3 --resume | tail -n 1 > /output_cli/153.txt

# SEQUENCIAS DE TAMANIO 100 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/154.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/155.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/156.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/157.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/158.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/159.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/160.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/161.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/162.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/163.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5 | tail -n 1 > /output_cli/164.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/4 ./data/large/5 --resume | tail -n 1 > /output_cli/165.txt

# SEQUENCIAS DE TAMANIO 1 000 000
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/166.txt
mpiexec -np 2 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/167.txt

mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/168.txt
mpiexec -np 4 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/169.txt

mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/170.txt
mpiexec -np 8 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/171.txt

mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/172.txt
mpiexec -np 12 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/173.txt

mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/174.txt
mpiexec -np 16 -hostfile $HOSTFILE ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/175.txt

mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7 | tail -n 1 > /output_cli/176.txt
mpiexec -np 1                      ./build/smith_waterman 2 ./data/large/6 ./data/large/7 --resume | tail -n 1 > /output_cli/176-.txt
