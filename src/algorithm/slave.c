#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "algorithm/slave.h"
#include "algorithm/algorithm.h"
#include "algorithm/blocks.h"
#include "runtime/messages.h"
#include "utils/reports.h"

void slave()
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    BlockParam *param_msg = malloc(sizeof(BlockParam));
    BlockResult *result_msg = malloc(sizeof(BlockResult));
    uint32_t *matrix = create_block(BLOCK_WIDTH + 1, BLOCK_HEIGHT + 1);
    if(matrix == NULL){
        // TODO precisa una mejor solucion
        //logging(rank, "failed to allocate matrix block\n");
        exit(EXIT_FAILURE);
    }
    MatrixCell *cell = malloc(sizeof(MatrixCell));

    MPI_Status status;

    CharArray *seq1 = malloc(sizeof(CharArray));
    CharArray *seq2 = malloc(sizeof(CharArray));

    // traceback
    char *matched_seq1 = calloc(BLOCK_WIDTH + BLOCK_HEIGHT, sizeof(char));
    char *matched_seq2 = calloc(BLOCK_WIDTH + BLOCK_HEIGHT, sizeof(char));
    Direction next_block = 0;
    TracebackResult *traceback_msg = malloc(sizeof(TracebackResult));
    uint32_t traceback_length = 0;

    while (true)
    {
        receive_BlockParam(param_msg, &status);

        if (status.MPI_TAG == TAG_TERMINATE)
        {
            //logging(rank, "received terminate signal");
            break;
        }

        seq1->data = param_msg->seq1;
        seq1->length = param_msg->block.width;
        seq2->data = param_msg->seq2;
        seq2->length = param_msg->block.height;

        //logging(rank, "receives block (%d, %d)", param_msg->block.i, param_msg->block.j);
        load_block(matrix, &param_msg->block);
        complete_block(matrix, cell, seq1, seq2);

        if (status.MPI_TAG == TAG_BLOCK_PARAM)
        {
            load_blockResult(result_msg, matrix, cell, param_msg);
            //logging(rank, "sending result for block (%d, %d) with max score %d ", result_msg->block.i, result_msg->block.j, result_msg->result.max_score);
            send_BlockResult(result_msg);
        }

        if (status.MPI_TAG == TAG_TRACEBACK_RUN)
        {
            // es la celda por la que debemos arrancar el traceback en este bloque
            cell->i = param_msg->block.max_cell.i;
            cell->j = param_msg->block.max_cell.j;
            cell->max_score = param_msg->block.max_cell.max_score;

            next_block = calculate_traceback_block(matched_seq1, matched_seq2, matrix, cell, &traceback_length, seq1->data, seq2->data);

            load_tracebackResult(traceback_msg, cell, next_block, param_msg, traceback_length, matched_seq1, matched_seq2);
            //logging(rank, " sending traceback result for block (%d, %d)", traceback_msg->block_i, traceback_msg->block_j);
            send_TracebackResult(traceback_msg, TAG_TRACEBACK_RESULT);
        }
    }

    free_BlockParam(param_msg);
    free_BlockResult(result_msg);
    free_TracebackResult(traceback_msg);
    free_block(matrix);
    free(cell);
    free(seq1);
    free(seq2);
    free(matched_seq1);
    free(matched_seq2);
}