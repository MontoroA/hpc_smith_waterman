#include <mpi.h>

#include "algorithm/master.h"
#include "algorithm/blocks.h"
#include "algorithm/algorithm.h"
#include "algorithm/primitives/primitives.h"
#include "algorithm/primitives/queue.h"

// PROCESO MASTER
void master(int len1, int len2, char *seq1, char *seq2)
{

    // preparar sus estructuras de control, mapa de bloques, etc
    BlockMap *map = create_Map(seq1, seq2);
    Queue *queue = createQueue(max(seq1->length, seq2->length));

    int nro_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &nro_procs);
    bool *proc_available = malloc((nro_procs + 1) * sizeof(bool));
    for (int i = 1; i <= nro_procs; i++)
    {
        proc_available[i] = true;
    }

    // solo se necesita 1 de cada para trabajar el master
    BlockParam *param_msg = create_blockParam();
    BlockResult *result_msg = create_blockResult();

    int cnxt_pid = 1;

    MatrixBlock *block = get_Block(map, 0, 0);

    load_BlockParam(param_msg, block, seq1, seq2);

    int count = 0;
    MPI_Request request;
    MPI_Status status;

    send_BlockParam(param_msg, cnxt_pid);

    int working_procs = 1;

    while (true)
    {
        receive_BlockResult(result_msg, &cnxt_pid, &status);
        if (status.MPI_TAG == TAG_BLOCK_RESULT)
        {
            // actualizo el bloque en el mapa
            update_BlockMap(result_msg->block, map);

            // agrego a la cola los nuevos bloques a procesar
            enqueue_newBlocks(queue, map, &result_msg->block);

            proc_available[cnxt_pid] = true;
            working_procs--;

            for (int i = 1; i <= nro_procs; i++)
            {
                if (proc_available[i])
                {
                    if (isEmpty(queue))
                        break;
                    block = dequeue(queue);
                    load_dependencies(block, map);
                    load_BlockParam(param_msg, block, len1, len2, seq1, seq2);
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

    // terminar slaves para que liberen su memoria y terminen
    for (int i = 0; i < nro_procs; i++)
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

MatrixBlock *get_Block(BlockMap *map, int i, int j)
{

    return &map->blocks[i * map->width + j];
}

void load_BlockParam(BlockParam *msg, MatrixBlock *block, char *seq1, char *seq2)
{
    msg->block = block;
    memcpy(msg->seq1, seq1 + block->i * BLOCK_WIDTH, block->width * sizeof(char));
    memcpy(msg->seq2, seq2 + block->j * BLOCK_HEIGHT, block->height * sizeof(char));
}

int send_BlockParam(BlockParam *msg, int dest)
{
    MPI_Send(msg, sizeof(BlockParam), MPI_BYTE, dest, TAG_BLOCK_PARAM, MPI_COMM_WORLD);
}

void receive_BlockResult(BlockResult *msg, int *cnxt_pid, MPI_Status *status)
{
    MPI_Recv(msg sizeof(BlockResult), MPI_BYTE, cnxt_pid, TAG_BLOCK_RESULT, MPI_COMM_WORLD, status);
}

void enqueue_newBlocks(Queue *queue, BlockMap *map, MatrixBlock *block)
{
    if (block->i < map->height - 1 && block->j < map->width - 1)
    {
        MatrixBlock *diag = get_MatrixBlock(block->i + 1, block->j + 1, map);
        enqueue(queue, diag);
    }

    if (block->j < map->width - 1)
    {
        MatrixBlock *der = get_MatrixBlock(block->i, block->j + 1, map);
        enqueue(queue, der);
    }

    if (block->i < map->height - 1)
    {
        MatrixBlock *inf = get_MatrixBlock(block->i + 1, block->j, map);
        enqueue(queue, inf);
    }
}