#include <stdio.h>
#include <stdlib.h>

#include "algorithm/primitives/primitives.h"
#include "algorithm/primitives/list.h"
#include "utils/utils.h"
#include "algorithm/blocks.h"

//TODO solucionar parametros: deberia recibir chararray con la subsequencia considerada
int max_val(int* matrix, int i, int j, char* seq1, char* seq2, int start_seq1, int start_seq2, int row_size) {
    int gap_penalty = W(1);
    int similarity = s(seq1[start_seq1 + i], seq2[start_seq2 + j]);
    
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


BlockResult* complete_block(int* matrix, CharArray* sequence1, CharArray* sequence2){
    char* seq1 = sequence1->data;
    char* seq2 = sequence2->data;
    int len1 = sequence1->length;
    int len2 = sequence2->length;

    // VERSION 2: ANTIDIAGONAL INICIAL
    // int tope_block_j = len2 + 1;
    // int max_i = 0, max_j = 0, max_score = 0;
    // int k;
    // int tope = len1 + len2 - 1;
    // for(k = 0 ; k <= tope ; k++){
    //     int init_i = min(k, len1);
    //     int stop_i = max(1, k - len2 + 2);
    //     for(int i = init_i ; i >= stop_i ; i--){
    //         int j = k-i;
    //         matrix[i*tope_block_j + j] = max_val(matrix, i, j, seq1, seq2, tope_block_j);
    //         if(matrix[i*tope_block_j + j] > max_score){
    //             max_score = matrix[i*tope_block_j + j];
    //             max_i = i;
    //             max_j = j;
    //         }
    //     }
    // }


    // VERSION 3: SECUENCIAL
    int i;
    int j;
    int max_i = 0, max_j = 0, max_score = 0;
    for(i = 1; i < (1 + len1) ; i++){
        for(j = 1; j < (1+ len2) ; j++){
            //TODO
            // matrix[i*(len2 + 1) + j] = max_val(matrix, i, j, seq1, seq2, len2+1);
            if(matrix[i*(len2 + 1) + j] > max_score){
                max_score = matrix[i*(len2 + 1) + j];
                max_i = i;
                max_j = j;
            }
        }
    }
    

    BlockResult* result = malloc(sizeof(BlockResult));
    result->result.i = max_i;
    result->result.j = max_j;
    result->result.max_score = max_score;

    // print_matrix(matrix, len1 + 1, len2 + 1);

    return result;
}


void traceback(int* matrix, MatrixCell* entry, CharArray* sequence1, CharArray* sequence2){
    char* seq1 = sequence1->data;
    char* seq2 = sequence2->data;
    int len2 = sequence2->length;
    // print_matrix(matrix, len1 + 1, len2 + 1);

    //Find max score and backtrack to find the longest common subsequence
    List* matched_seq1 = NULL;
    List* matched_seq2 = NULL;
    int i = entry->i;
    int j = entry->j;
    int current_score = entry->max_score;
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
    free(matched_seq1);
    free(matched_seq2);
}


