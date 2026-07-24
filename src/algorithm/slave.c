#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>
#include "algorithm/slave.h"
#include "algorithm/algorithm.h"
#include "hpc/mpi_handler.h"
#include "algorithm/blocks.h"

void slave()
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("(process %d) initialized \n", rank);
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
        printf("(process %d) waiting for data \n", rank);
        MPI_Recv(param_msg,
                 sizeof(BlockParam),
                 MPI_BYTE,
                 MASTER_RANK,
                 MPI_ANY_TAG,
                 MPI_COMM_WORLD,
                 &status);

        if (status.MPI_TAG == TAG_TERMINATE)
        {
            printf("(process %d) received terminate signal \n", rank);
            break;
        }

        if (status.MPI_TAG == TAG_BLOCK_PARAM)
        {
            printf("(process %d) receives block (%d, %d)\n", rank, param_msg->block.i, param_msg->block.j);
            load_block(matrix, param_msg);

            seq1->data = param_msg->seq1;
            seq1->length = param_msg->block.width;
            seq2->data = param_msg->seq2;
            seq2->length = param_msg->block.height;

            printf("(process %d) working on block (%d, %d)\n", rank, param_msg->block.i, param_msg->block.j);
            complete_block(matrix, max_cell, seq1, seq2);

            load_blockResult(result_msg, matrix, max_cell, param_msg);
            printf("(process %d) sending result for block (%d, %d) with max score %d \n", rank, result_msg->block.i, result_msg->block.j, result_msg->result.max_score);
            MPI_Send(result_msg,
                     sizeof(BlockResult),
                     MPI_BYTE,
                     MASTER_RANK,
                     TAG_BLOCK_RESULT,
                     MPI_COMM_WORLD);
        }

        if (status.MPI_TAG == TAG_TRACEBACK_RUN || status.MPI_TAG == TAG_TRACEBACK_NEIGHBOUR)
        {
            printf("(process %d) receives block (%d, %d) for traceback\n", rank, param_msg->block.i, param_msg->block.j);
            load_block(matrix, param_msg);

            seq1->data = param_msg->seq1;
            seq1->length = param_msg->block.width;
            seq2->data = param_msg->seq2;
            seq2->length = param_msg->block.height;

            printf("(process %d) working on traceback for block (%d, %d)\n", rank, param_msg->block.i, param_msg->block.j);
            complete_block(matrix, max_cell, seq1, seq2);

            traceback_msg->block_i = param_msg->block.i;
            traceback_msg->block_j = param_msg->block.j;

            if (status.MPI_TAG == TAG_TRACEBACK_NEIGHBOUR)
            {
                printf("(process %d) sending traceback neighbour ready for block (%d, %d)\n", rank, traceback_msg->block_i, traceback_msg->block_j);
                MPI_Send(traceback_msg,
                         sizeof(TracebackResult),
                         MPI_BYTE,
                         MASTER_RANK,
                         TAG_TRACEBACK_NEIGHBOUR_READY,
                         MPI_COMM_WORLD);
            }
            else
            {
                next_block = calculate_traceback_block(matched_seq1, matched_seq2, matrix, starting_cell, seq1->data, seq2->data);

                load_tracebackResult(traceback_msg, starting_cell, next_block, param_msg, matched_seq1, matched_seq2);

                printf("(process %d) sending traceback result for block (%d, %d) \n", rank, traceback_msg->block_i, traceback_msg->block_j);
                MPI_Send(traceback_msg,
                         sizeof(TracebackResult),
                         MPI_BYTE,
                         MASTER_RANK,
                         TAG_TRACEBACK_RESULT,
                         MPI_COMM_WORLD);
            }
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