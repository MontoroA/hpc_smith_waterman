#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "algorithm/algorithm.h"
#include "collections/list.h"
#include "collections/arrays.h"
#include "algorithm/blocks.h"

uint32_t max_val(uint32_t *matrix, uint32_t i, uint32_t j, char *seq1, char *seq2)
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
    return (uint32_t)max;
}

Direction reverse_max_val(uint32_t *matrix, uint32_t i, uint32_t j, char *seq1, char *seq2)
{
    int diag = matrix[(i - 1) * (BLOCK_WIDTH + 1) + (j - 1)] + s(seq1[j - 1], seq2[i - 1]);
    int sup = matrix[(i - 1) * (BLOCK_WIDTH + 1) + j] + W(1);
    // int izq = matrix[i * BLOCK_WIDTH + (j - 1)] + W(1);

    if (matrix[i * (BLOCK_WIDTH + 1) + j] == diag)
        return DIAG;
    if (matrix[i * (BLOCK_WIDTH + 1) + j] == sup)
        return UP;
    else
        return LEFT;
}

void print_matrix(uint32_t *matrix, CharArray *sequence1, CharArray *sequence2)
{
    uint32_t rows = sequence2->length + 1;
    uint32_t cols = sequence1->length + 1;
    uint32_t row_size = BLOCK_WIDTH + 1;

    printf("       ");
    for (uint32_t j = 0; j < cols; j++)
    {
        if (j == 0)
            printf("       ");
        else
            printf("%6c ", sequence1->data[j - 1]);
    }
    printf("\n");

    for (uint32_t i = 0; i < rows; i++)
    {
        if (i == 0)
            printf("       ");
        else
            printf("%6c ", sequence2->data[i - 1]);

        for (uint32_t j = 0; j < cols; j++)
        {
            printf("%6d ", matrix[i * row_size + j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void complete_block(uint32_t *matrix, MatrixCell *max_cell, CharArray *sequence1, CharArray *sequence2)
{
    char *seq1 = sequence1->data;
    char *seq2 = sequence2->data;
    uint32_t nro_cols = sequence1->length;
    uint32_t nro_rows = sequence2->length;

    uint32_t i, j;
    uint32_t max_i = 0, max_j = 0, max_score = 0;

    for (i = 0; i < nro_rows; i++)
    {
        for (j = 0; j < nro_cols; j++) //
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

Direction calculate_traceback_block(char *matched_seq1, char *matched_seq2, uint32_t *matrix, MatrixCell *cell, uint32_t *traceback_length, char *seq1, char *seq2)
{
    uint32_t i = cell->i;
    uint32_t j = cell->j;
    uint32_t current_score = cell->max_score;
    uint32_t k = 0;

    while (j > 0 && i > 0 && current_score > 0)
    {
        Direction dir = reverse_max_val(matrix, i, j, seq1, seq2);
        if (dir == DIAG)
        {
            matched_seq1[k] = seq1[j - 1];
            matched_seq2[k] = seq2[i - 1];
            i--;
            j--;
        }
        else if (dir == UP)
        {
            matched_seq1[k] = '_';
            matched_seq2[k] = seq2[i - 1];
            i--;
        }
        else
        {
            matched_seq1[k] = seq1[j - 1];
            matched_seq2[k] = '_';
            j--;
        }

        k++;
        current_score = matrix[i * (BLOCK_WIDTH + 1) + j];
    }

    cell->i = i;
    cell->j = j;
    cell->max_score = current_score;
    *traceback_length = k;

    if (i == 0 && j == 0)
    {
        return DIAG;
    }
    else if (j == 0)
    {
        return LEFT;
    }
    else
    {
        return UP;
    }
}
