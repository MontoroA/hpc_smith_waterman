#include <stdio.h>
#include <mpi.h>

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
    while (true)
    {
        print(rank, "waiting for data\n");
        MPI_Recv(param_msg,
                 sizeof(BlockParam),
                 MPI_BYTE,
                 MASTER_RANK,
                 MPI_ANY_TAG,
                 MPI_COMM_WORLD,
                 &status);
        
        if (status.MPI_TAG == TAG_TERMINATE)
        {
            print(rank, "received terminate signal\n");
            break;
        }

        if (status.MPI_TAG == TAG_BLOCK_PARAM)
        {
            print(rank, "receives block (%d, %d)\n", param_msg->block.i, param_msg->block.j);
            load_block(matrix, &param_msg->block);

            
            seq1->data = param_msg->seq1;
            seq1->length = param_msg->block.width;
            seq2->data = param_msg->seq2;
            seq2->length = param_msg->block.height;
            
            // printf("working on block (%d, %d)\n", param_msg->block.i, param_msg->block.j);
            // printf("Size of seq1: %d, Size of seq2: %d\n", seq1->length, seq2->length);
            // printf("Seq1: %.*s\n", seq1->length, seq1->data);
            // printf("Seq2: %.*s\n", seq2->length, seq2->data);
            complete_block(matrix, max_cell, seq1, seq2);

            load_blockResult(result_msg, matrix, max_cell, param_msg);
            print(rank, "sending result for block (%d, %d) with max score %d\n", result_msg->block.i, result_msg->block.j, result_msg->result.max_score);
            MPI_Send(result_msg,
                     sizeof(BlockResult),
                     MPI_BYTE,
                     MASTER_RANK,
                     TAG_BLOCK_RESULT,
                     MPI_COMM_WORLD);
        }
    }
    free_BlockParam(param_msg);
    free_BlockResult(result_msg);
    free_block(matrix);
    free(max_cell);
    free(seq1);
    free(seq2);
}