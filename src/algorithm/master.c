#include <mpi.h>
#include <string.h>
#include <stdio.h>

#include "algorithm/master.h"
#include "algorithm/blocks.h"
#include "algorithm/algorithm.h"
#include "algorithm/primitives/primitives.h"
#include "algorithm/primitives/queue.h"
#include "utils/reports.h"



MatrixBlock *get_Block(BlockMap *map, int i, int j)
{
    return &map->blocks[i * map->width + j];
}


void load_BlockParam(BlockParam *msg, MatrixBlock *block, CharArray *seq1, CharArray *seq2)
{
    msg->block = *block;
    char* start_seq1 = seq1->data + block->i * BLOCK_WIDTH;
    char* start_seq2 = seq2->data + block->j * BLOCK_HEIGHT;
    memcpy(msg->seq1, start_seq1, block->width);
    memcpy(msg->seq2, start_seq2, block->height);
}


int send_BlockParam(BlockParam *msg, int dest)
{
    MPI_Send(msg, sizeof(BlockParam), MPI_BYTE, dest, TAG_BLOCK_PARAM, MPI_COMM_WORLD);
    return 0; //TODO por que un int?
}


void receive_BlockResult(BlockResult *msg, MPI_Status *status)
{
    MPI_Recv(msg, sizeof(BlockResult), MPI_BYTE, MPI_ANY_SOURCE, TAG_BLOCK_RESULT, MPI_COMM_WORLD, status);
}


void enqueue_ready_blocks(Queue *queue, BlockMap *map, MatrixBlock *block)
{
    int i = block->i;
    int j = block->j;
    int width = map->width;
    int height = map->height;

    if (i < (height - 1) && j < (width - 1))
    {
        MatrixBlock *diag = get_MatrixBlock(i + 1, j + 1, map);
        if(block_is_ready(diag, map)){
            load_dependencies(diag,map);
            enqueue(queue, *diag);
            print(MASTER_RANK, "enqueued block (%d, %d)\n", diag->i, diag->j);
        }
    }
    
    if (j < (width - 1))
    {
        MatrixBlock *der = get_MatrixBlock(i, j + 1, map);
        if(block_is_ready(der, map)){
            load_dependencies(der,map);
            enqueue(queue, *der);
            print(MASTER_RANK, "enqueued block (%d, %d)\n", der->i, der->j);
        }
    }
    
    if (i < (height - 1))
    {
        MatrixBlock *inf = get_MatrixBlock(i + 1, j, map);
        if(block_is_ready(inf, map)){
            load_dependencies(inf,map);
            enqueue(queue, *inf);
            print(MASTER_RANK, "enqueued block (%d, %d)\n", inf->i, inf->j);
        }
    }
}




void master(CharArray *seq1, CharArray *seq2)
{
    print(MASTER_RANK, "initialized\n");
    BlockMap *map = create_Map(seq1, seq2);
    Queue *queue = createQueue(max(seq1->length, seq2->length));
    
    int nro_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &nro_procs);
    bool *proc_available = malloc(nro_procs * sizeof(bool));
    for (int i = 1; i < nro_procs; i++)
    {
        proc_available[i] = true;
    }

    BlockResult *result_msg = create_blockResult();
    BlockParam *param_msg = create_blockParam();
    MatrixBlock *block = get_Block(map, 0, 0);
    //row and col of 0s
    // for(int i = 0; i < BLOCK_WIDTH; i++){
    //     block->row[i] = 0;
    // }
    // for(int i = 0; i < BLOCK_HEIGHT; i++){
    //     block->col[i] = 0;
    // }
    // block->diag = 0;
    load_dependencies(block,map);

    load_BlockParam(param_msg, block, seq1, seq2);
    

    print(MASTER_RANK, "ready for distributing work\n");
    // int count = 0;
    // MPI_Request request;
    int cnxt_pid = 1;
    MPI_Status status;
    send_BlockParam(param_msg, cnxt_pid);

    int working_procs = 1;

    while (true)
    {
        receive_BlockResult(result_msg, &status);
        cnxt_pid = status.MPI_SOURCE;
        print(MASTER_RANK, "received result for block (%d, %d) from process %d\n", result_msg->block.i, result_msg->block.j, cnxt_pid);
        if (status.MPI_TAG == TAG_BLOCK_RESULT)
        {
            update_BlockMap(result_msg->block, map);
            enqueue_ready_blocks(queue, map, &result_msg->block);

            proc_available[cnxt_pid] = true;
            working_procs--;

            for (int i = 1; i < nro_procs; i++)
            {
                if (proc_available[i])
                {
                    if (isEmpty(queue))
                        break;
                    block = dequeue(queue);
                    print(MASTER_RANK, "popped block (%d, %d): sent to process %d\n", block->i, block->j, i);
                    load_BlockParam(param_msg, block, seq1, seq2);
                    send_BlockParam(param_msg, i);
                    proc_available[i] = false;
                    working_procs++;
                }
            }

            if (isEmpty(queue) && working_procs == 0)
            {
                break;
            }
        }
    }

    // traceback(matrix, res, seq1, seq2);
    // print_block_map(map, seq1, seq2);
 
    for (int i = 1; i < nro_procs; i++)
    {
        // TODO: el master_rank es 0, hay que ver que ningun salve tenga el mismo indicador
        MPI_Send(NULL,
                 0,
                 MPI_BYTE,
                 i,
                 TAG_TERMINATE,
                 MPI_COMM_WORLD);
    }

    free(map);
    free(proc_available);
    free(queue);
}