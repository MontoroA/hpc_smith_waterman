#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "list.h"

int max_val(int* matrix, int i, int j, char* seq1, char* seq2, int row_size){
    int gap_penalty = W(1);
    int similarity = s(seq1[i], seq2[j]);
    
    int* prev_row = matrix + ((i-1) * row_size);
    int* curr_row = matrix + (i * row_size);
    int diag = prev_row[j-1] + similarity;
    int sup = prev_row [j] + gap_penalty;
    int izq = curr_row [j-1] + gap_penalty;

    int max = diag;
    if (sup > max) max = sup;
    if (izq > max) max = izq;
    if (max < 0) max = 0;
    return max;
}

Direction reverse_max_val(int* matrix, int i, int j, char* seq1, char* seq2, int row_size){
    int diag = matrix[(i-1) *  row_size  +    (j-1) ] + s(seq1[i], seq2[j]);
    int sup =  matrix[(i-1) *  row_size  +     j    ] + W(1);
    // int izq =  matrix[ i    *  row_size     + (j-1) ] + W(1);

    if(matrix[i * row_size + j] == diag)
        return DIAG;
    if(matrix[i * row_size + j] == sup)
        return UP;
    else
        return LEFT;
}

void print_matrix(int* matrix, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            int val = matrix[i * cols + j];
            if(0 <= val && val < 10)
                printf(" %d ", val);
            else
                printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

void run(char* seq1, char* seq2, int len1, int len2){
    int* matrix = malloc((1 + len1) * (1 + len2) * sizeof(int));

    //put 0s in first row 
    for(int j = 0; j < (1 + len2) ; j++){
        matrix[j] = 0;
    }
    //and first column
    for(int i = 0; i < (1 + len1) ; i++){
        matrix[i * (len2 + 1)] = 0;
    }



    //Complete the matrix
    int i;
    int j;
    int max_i = 0, max_j = 0, max_score = 0;
    for(i = 1; i < (1 + len1) ; i++){
        for(j = 1; j < (1+ len2) ; j++){
            matrix[i*(len2 + 1) + j] = max_val(matrix, i, j, seq1, seq2, len2+1);
            if(matrix[i*(len2 + 1) + j] > max_score){
                max_score = matrix[i*(len2 + 1) + j];
                max_i = i;
                max_j = j;
            }
        }
    }

    //print_matrix(matrix, len1 + 1, len2 + 1);

    //Find max score and backtrack to find the longest common subsequence
    List* matched_seq1 = NULL;
    List* matched_seq2 = NULL;
    i = max_i;
    j = max_j;
    int current_score = max_score;
    do{
        Direction dir = reverse_max_val(matrix, i, j, seq1, seq2, len2 + 1);
        char val_seq1 = seq1[i];
        char val_seq2 = seq2[j];
        char gap = '_';
        if(dir == DIAG){
            push(&matched_seq1, val_seq1);
            push(&matched_seq2, val_seq2);
            i--;
            j--;
        }
        else if(dir == UP){
            push(&matched_seq1, val_seq1);
            push(&matched_seq2, gap);
            i--;
        }
        else{
            push(&matched_seq1, gap);
            push(&matched_seq2, val_seq2);
            j--;
        }
        current_score = matrix[i * (len2 + 1) + j];
    } while(current_score > 0);
    print(matched_seq1);
    print(matched_seq2);

    //Free memory
    free(matrix);
    free(matched_seq1);
    free(matched_seq2);
}