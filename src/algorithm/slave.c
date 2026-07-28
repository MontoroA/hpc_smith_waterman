#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>
#include "algorithm/slave.h"
#include "algorithm/algorithm.h"
#include "hpc/mpi_handler.h"
#include "algorithm/blocks.h"
#include "utils/reports.h"

void slave()
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    BlockParam *param_msg = malloc(sizeof(BlockParam));
    BlockResult *result_msg = malloc(sizeof(BlockResult));
    int *matrix = create_block(BLOCK_WIDTH + 1, BLOCK_HEIGHT + 1);
    MatrixCell *max_cell = malloc(sizeof(MatrixCell));

    MPI_Status status;

    CharArray *seq1 = malloc(sizeof(CharArray));
    CharArray *seq2 = malloc(sizeof(CharArray));

    // traceback
    char *matched_seq1 = malloc(BLOCK_WIDTH * sizeof(char));
    char *matched_seq2 = malloc(BLOCK_HEIGHT * sizeof(char));
    Direction next_block = 0;
    TracebackResult *traceback_msg = malloc(sizeof(TracebackResult));
    MatrixCell *starting_cell = malloc(sizeof(MatrixCell));

    printf("(process %d) ready to work \n", rank);
    while (true)
    {
        print(rank, "waiting for data\n");
        receive_BlockParam(param_msg, &status);

        if (status.MPI_TAG == TAG_TERMINATE)
        {
            print(rank, "received terminate signal\n");
            break;
        }

        seq1->data = param_msg->seq1;
        seq1->length = param_msg->block.width;
        seq2->data = param_msg->seq2;
        seq2->length = param_msg->block.height;

        if (status.MPI_TAG != TAG_TRACEBACK_RUN)
        {
            print(rank, "receives block (%d, %d)\n", param_msg->block.i, param_msg->block.j);
            load_block(matrix, &param_msg->block);

            printf("(process %d) working on block (%d, %d)\n", rank, param_msg->block.i, param_msg->block.j);
            complete_block(matrix, max_cell, seq1, seq2);

            if (status.MPI_TAG == TAG_BLOCK_PARAM)
            {
                load_blockResult(result_msg, matrix, max_cell, param_msg);
                printf("(process %d) sending result for block (%d, %d) with max score %d \n", rank, result_msg->block.i, result_msg->block.j, result_msg->result.max_score);
                send_BlockResult(result_msg);
            }

            if (status.MPI_TAG == TAG_TRACEBACK_NEIGHBOUR)
            {
                // aviso al master que este bloque ya se calculo por adelantado
                printf("(process %d) sending traceback neighbour ready for block (%d, %d)\n", rank, traceback_msg->block_i, traceback_msg->block_j);
                send_TracebackResult(traceback_msg, TAG_TRACEBACK_NEIGHBOUR_READY);
            }

            if (status.MPI_TAG == TAG_TRACEBACK_FIRST_RUN)
            {
                // es la celda por la que debemos arrancar el traceback en este bloque
                starting_cell = &param_msg->block.max_cell;
                next_block = calculate_traceback_block(matched_seq1, matched_seq2, matrix, starting_cell, seq1->data, seq2->data);

                load_tracebackResult(traceback_msg, starting_cell, next_block, param_msg, matched_seq1, matched_seq2);

                printf("(process %d) sending traceback result for block (%d, %d) \n", rank, traceback_msg->block_i, traceback_msg->block_j);
                send_TracebackResult(traceback_msg, TAG_TRACEBACK_RESULT);
            }
        }
        else
        {
            // es la celda por la que debemos arrancar el traceback en este bloque
            starting_cell = &param_msg->block.max_cell;
            next_block = calculate_traceback_block(matched_seq1, matched_seq2, matrix, starting_cell, seq1->data, seq2->data);

            load_tracebackResult(traceback_msg, starting_cell, next_block, param_msg, matched_seq1, matched_seq2);

            printf("(process %d) sending traceback result for block (%d, %d) \n", rank, traceback_msg->block_i, traceback_msg->block_j);
            send_TracebackResult(traceback_msg, TAG_TRACEBACK_RESULT);
        }
    }

    free_BlockParam(param_msg);
    free_BlockResult(result_msg);
    free_TracebackResult(traceback_msg);
    free_block(matrix);
    free(max_cell);
    free(seq1);
    free(seq2);
    free(matched_seq1);
    free(matched_seq2);
}