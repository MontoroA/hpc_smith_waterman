#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "algorithm.h"

int main(){
    //TODO if no arguments, load default sequences from files
    int len1 = 0;
    int len2 = 0;
    char *seq1 = NULL, *seq2 = NULL;

    int err = load_sequence("sequences/seq1.txt", &seq1, &len1);
    if(err == 1){
        printf("Error loading sequences\n");
        return 1;
    }
    err = load_sequence("sequences/seq2.txt", &seq2, &len2);
    if(err == 1){
        printf("Error loading sequences\n");
        return 1;
    }    

    run(seq1, seq2, len1, len2);
    free(seq1);
    free(seq2);
    return 0;
}