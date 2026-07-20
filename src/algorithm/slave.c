#include <mpi.h>

#include "algorithm/slave.h"
#include "algorithm/algorithm.h"
#include "hpc/mpi_handler.h"

void slave()
{
    BlockParam *param_msg = malloc(sizeof(BlockParam));
    BlockResult *result_msg = malloc(sizeof(BlockResult));
    int *matrix = create_block(BLOCK_WIDTH + 1, BLOCK_HEIGHT + 1);
    BlockResult *result = malloc(sizeof(BlockResult));

    MPI_Status status;

    CharArray *seq1 = malloc(sizeof(CharArray));
    CharArray *seq2 = malloc(sizeof(CharArray));

    while (true)
    {
        MPI_Recv(param_msg,
                 sizeof(BlockParam),
                 MPI_BYTE,
                 MASTER_RANK,
                 MPI_ANY_TAG,
                 MPI_COMM_WORLD,
                 &status);

        if (status.MPI_TAG == TAG_TERMINATE)
        {
            break;
        }

        if (status.MPI_TAG == TAG_BLOCK_PARAM)
        {
            load_block(matrix, param_msg);

            seq1->data = param_msg->seq1;
            seq1->length = param_msg->block.width;
            seq2->data = param_msg->seq2;
            seq2->length = param_msg->block.height;

            complete_block(matrix, result, seq1, seq2);

            load_resultBlock(result_msg, matrix, result, param_msg);

            MPI_Send(result_msg,
                     sizeof(BlockResultMessage),
                     MPI_BYTE,
                     MASTER_RANK,
                     TAG_BLOCK_RESULT,
                     MPI_COMM_WORLD);
        }
    }
    free_BlockParam(param_msg);
    free_BlockResult(result_msg);
    free_block(matrix);
    free(result);
    free(seq1);
    free(seq2);
}