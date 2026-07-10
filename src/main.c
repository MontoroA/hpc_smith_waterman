#include <stdio.h>
#include <stdlib.h>

#include "utils/io.h"
#include "utils/sequences.h"
#include "algorithm/algorithm.h"
#include <omp.h>


int main(int argc, char** argv){
    int mode = read_mode(argc, argv);
    if(mode == MODE_INVALID){
        printf("Error leyendo modo: puede ser porque el modo fue incorrecto, o porque la cantidad de parámetros no fue especificada\n");
        return EXIT_FAILURE;
    }
    char** params = argv + 2;

    double start = 0;
    double end = 0;

    Sequence** seqs = execute_mode(mode, params);
    if(seqs != NULL){
        char* seq1 = seqs[0]->data;
        char* seq2 = seqs[1]->data;
        int len1 = seqs[0]->length;
        int len2 = seqs[1]->length;
        start = omp_get_wtime(); // Start measuring time with OpenMP
        run(seq1, seq2, len1, len2);
        end = omp_get_wtime();
        printf("\nFinished execution in %f seconds\n", end - start);
        free(seq1);
        free(seq2);
    }
    return EXIT_SUCCESS;
}