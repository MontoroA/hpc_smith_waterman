#include <stdio.h>
#include <stdlib.h>

#include "algorithm/primitives/primitives.h"
#include "algorithm/primitives/list.h"
#include "utils/utils.h"
#include "algorithm/blocks.h"

int max_val(int *matrix, int i, int j, char *seq1, char *seq2)
{
    int gap_penalty = W(1);
    int similarity = s(seq1[j], seq2[i]);

    int *prev_row = matrix + (i * (BLOCK_WIDTH + 1));
    int *curr_row = matrix + ((i + 1) * (BLOCK_WIDTH + 1));
    int diag = prev_row[j] + similarity;
    int sup = prev_row[j + 1] + gap_penalty;
    int izq = curr_row[j] + gap_penalty;

    int max = diag;
    if (sup > max)
        max = sup;
    if (izq > max)
        max = izq;
    if (max < 0)
        max = 0;
    return max;
}

Direction reverse_max_val(int *matrix, int i, int j, char *seq1, char *seq2, int row_size)
{
    int diag = matrix[(i - 1) * row_size + (j - 1)] + s(seq1[i], seq2[j]);
    int sup = matrix[(i - 1) * row_size + j] + W(1);
    // int izq =  matrix[ i    *  row_size     + (j-1) ] + W(1);

    if (matrix[i * row_size + j] == diag)
        return DIAG;
    if (matrix[i * row_size + j] == sup)
        return UP;
    else
        return LEFT;
}

void print_matrix(int *matrix, CharArray *sequence1, CharArray *sequence2)
{
    int rows = sequence2->length + 1;
    int cols = sequence1->length + 1;
    int row_size = BLOCK_WIDTH + 1;

    printf("       ");
    for(int j = 0; j < cols; j++){
        if(j == 0) printf("       ");
        else printf("%6c ", sequence1->data[j-1]);
    }
    printf("\n");

    for (int i = 0; i < rows; i++)
    {
        if(i == 0) printf("       ");
        else printf("%6c ", sequence2->data[i-1]);

        for (int j = 0; j < cols; j++)
        {
            printf("%6d ", matrix[i * row_size + j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void complete_block(int *matrix, MatrixCell *max_cell, CharArray *sequence1, CharArray *sequence2)
{
    char *seq1 = sequence1->data;
    char *seq2 = sequence2->data;
    int nro_rows = sequence1->length;
    int nro_cols = sequence2->length;

    int i;
    int j;
    int max_i = 0, max_j = 0, max_score = 0;

    for (i = 0; i < nro_cols; i++) 
    {
        for (j = 0; j < nro_rows; j++) //
        {
            matrix[(i + 1) * (BLOCK_WIDTH + 1) + (j + 1)] = max_val(matrix, i, j, seq1, seq2);
            if (matrix[(i + 1) * (BLOCK_WIDTH + 1) + (j + 1)] > max_score)
            {
                max_score = matrix[(i + 1) * (BLOCK_WIDTH + 1) + (j + 1)];
                max_i = i + 1;
                max_j = j + 1;
            }
        }
    }

    max_cell->i = max_i;
    max_cell->j = max_j;
    max_cell->max_score = max_score;
    
    // print_matrix(matrix, sequence1, sequence2);
}

void traceback(int *matrix, MatrixCell *entry, CharArray *sequence1, CharArray *sequence2)
{
    char *seq1 = sequence1->data;
    char *seq2 = sequence2->data;
    int len2 = sequence2->length;
    // print_matrix(matrix, len1 + 1, len2 + 1);

    // Find max score and backtrack to find the longest common subsequence
    List *matched_seq1 = NULL;
    List *matched_seq2 = NULL;
    int i = entry->i;
    int j = entry->j;
    int current_score = entry->max_score;
    do
    {
        Direction dir = reverse_max_val(matrix, i, j, seq1, seq2, len2 + 1);
        char val_seq1 = seq1[i];
        char val_seq2 = seq2[j];
        char gap = '_';
        if (dir == DIAG)
        {
            push(&matched_seq1, val_seq1);
            push(&matched_seq2, val_seq2);
            i--;
            j--;
        }
        else if (dir == UP)
        {
            push(&matched_seq1, val_seq1);
            push(&matched_seq2, gap);
            i--;
        }
        else
        {
            push(&matched_seq1, gap);
            push(&matched_seq2, val_seq2);
            j--;
        }
        current_score = matrix[i * (len2 + 1) + j];
    } while (current_score > 0);
    print_list(matched_seq1);
    print_list(matched_seq2);

    // Free memory
    free(matched_seq1);
    free(matched_seq2);
}
