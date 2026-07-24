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

Direction reverse_max_val(int *matrix, int i, int j, char *seq1, char *seq2)
{
    int diag = matrix[(i - 1) * BLOCK_WIDTH + (j - 1)] + s(seq1[j - 1], seq2[i - 1]);
    int sup = matrix[(i - 1) * BLOCK_WIDTH + j] + W(1);
    // int izq = matrix[i * BLOCK_WIDTH + (j - 1)] + W(1);

    if (matrix[i * BLOCK_WIDTH + j] == diag)
        return DIAG;
    if (matrix[i * BLOCK_WIDTH + j] == sup)
        return UP;
    else
        return LEFT;
}

void print_matrix(int *matrix, CharArray *sequence1, CharArray *sequence2)
{
    int rows = sequence2->length + 1;
    int cols = sequence1->length + 1;
    int row_size = BLOCK_WIDTH + 1;

    printf("   ");
    for (int j = 0; j < cols; j++)
    {
        if (j == 0)
            printf("   ");
        else
            printf(" %c ", sequence1->data[j - 1]);
    }
    printf("\n");
    for (int i = 0; i < rows; i++)
    {
        if (i == 0)
            printf("   ");
        else
            printf(" %c ", sequence2->data[i - 1]);
        for (int j = 0; j < cols; j++)
        {
            int val = matrix[i * row_size + j];
            if (0 <= val && val < 10)
                printf(" %d ", val);
            else
                printf("%d ", matrix[i * row_size + j]);
        }
        printf("\n");
    }
}

void complete_block(int *matrix, MatrixCell *max_cell, CharArray *sequence1, CharArray *sequence2)
{
    char *seq1 = sequence1->data;
    char *seq2 = sequence2->data;
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

    /* <!> seq1 es la de arriba y seq2 la de la derecha <!>*/

    for (i = 0; i < len2; i++) // i itera en las filas
    {
        for (j = 0; j < len1; j++) // j itera en las columnas
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

Direction calculate_traceback_block(char *matched_seq1, char *matched_seq2, int *matrix, MatrixCell *starting_cell, char *seq1, char *seq2)
{
    int i = starting_cell->i;
    int j = starting_cell->j;
    int current_score = starting_cell->max_score;

    while (j > 0 && i > 0)
    {
        Direction dir = reverse_max_val(matrix, i, j, seq1, seq2);
        if (dir == DIAG)
        {
            matched_seq1[j - 1] = seq1[j - 1];
            matched_seq2[i - 1] = seq2[i - 1];
            i--;
            j--;
        }
        else if (dir == UP)
        {
            matched_seq1[j] = '_';
            matched_seq2[i - 1] = seq2[i - 1];
            i--;
        }
        else
        {
            matched_seq1[j - 1] = seq1[j - 1];
            matched_seq2[i] = '_';
            j--;
        }
        current_score = matrix[i * BLOCK_WIDTH + j];
    }

    starting_cell->i = i;
    starting_cell->j = j;
    starting_cell->max_score = current_score;

    if (i == 0 && j == 0)
    {
        return DIAG;
    }
    else if (i == 0)
    {
        return LEFT;
    }
    else
    {
        return UP;
    }
}
