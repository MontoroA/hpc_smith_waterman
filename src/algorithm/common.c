#include "algorithm/common.h"

CharArray *seq1;
CharArray *seq2;
BlockMap *map;
Queue *queue;
bool *proc_available;
BlockResult *result_msg;
BlockParam *param_msg;
MatrixBlock *block;
int nro_procs;
int cnxt_pid;
int working_procs;
MPI_Status status;
MatrixBlock *max_score_block;
TracebackResult *traceback_msg;
FILE *checkpoint;
uint32_t wavefront_number = 0;
List *matched_seq1 = NULL;
List *matched_seq2 = NULL;

uint32_t *matrix;
MatrixCell *cell;

void enqueue_ready_blocks(Queue *queue, BlockMap *map, MatrixBlock *block)
{
    uint32_t i = block->i;
    uint32_t j = block->j;
    uint32_t width = map->width;
    uint32_t height = map->height;

    if (i < (height - 1) && j < (width - 1))
    {
        MatrixBlock *diag = get_MatrixBlock(i + 1, j + 1, map);
        if (!diag->is_queued && block_is_ready(diag, map))
        {
            load_dependencies(diag, map);
            enqueue(queue, diag);
            logging(MASTER_RANK, "enqueued block (%d, %d)\n", diag->i, diag->j);
        }
    }

    if (j < (width - 1))
    {
        MatrixBlock *der = get_MatrixBlock(i, j + 1, map);
        if (!der->is_queued && block_is_ready(der, map))
        {
            load_dependencies(der, map);
            enqueue(queue, der);
            logging(MASTER_RANK, "enqueued block (%d, %d)\n", der->i, der->j);
        }
    }

    if (i < (height - 1))
    {
        MatrixBlock *inf = get_MatrixBlock(i + 1, j, map);
        if (!inf->is_queued && block_is_ready(inf, map))
        {
            load_dependencies(inf, map);
            enqueue(queue, inf);
            logging(MASTER_RANK, "enqueued block (%d, %d)\n", inf->i, inf->j);
        }
    }
}

void update_Traceback(TracebackResult *traceback_msg, List **matched_seq1, List **matched_seq2)
{
    for (uint32_t j = 0; j < traceback_msg->length; j++)
    {
        push(matched_seq1, traceback_msg->matched_seq1[j]);
    }

    for (uint32_t i = 0; i < traceback_msg->length; i++)
    {
        push(matched_seq2, traceback_msg->matched_seq2[i]);
    }
}

MatrixBlock *get_NextBlockTraceback(BlockMap *map, TracebackResult *traceback_msg)
{
    uint32_t i = traceback_msg->block_i;
    uint32_t j = traceback_msg->block_j;

    if (traceback_msg->next_block == DIAG && (i > 0) && (j > 0))
    {
        return get_MatrixBlock(i - 1, j - 1, map);
    }
    else if (traceback_msg->next_block == UP && (i > 0))
    {
        return get_MatrixBlock(i - 1, j, map);
    }
    else if (traceback_msg->next_block == LEFT && (j > 0))
    {
        return get_MatrixBlock(i, j - 1, map);
    }
    else
    {
        return NULL;
    }
}

void load_NextStartingCell(TracebackResult *traceback_msg, MatrixBlock *block)
{
    if (traceback_msg->next_block == DIAG)
    {
        block->max_cell.i = block->height; //traceback_msg->next_starting_cell.i + block->height - 1;
        block->max_cell.j = block->width; //traceback_msg->next_starting_cell.j + block->width - 1;
    }
    else if (traceback_msg->next_block == UP)
    {
        block->max_cell.i = block->height; //traceback_msg->next_starting_cell.i + block->height - 1;
        block->max_cell.j = traceback_msg->next_starting_cell.j;
    }
    else if (traceback_msg->next_block == LEFT)
    {
        block->max_cell.i = traceback_msg->next_starting_cell.i;
        block->max_cell.j = block->width; //traceback_msg->next_starting_cell.j + block->width - 1;
    }

    block->max_cell.max_score = traceback_msg->next_starting_cell.max_score;
}
