#include <mpi.h>
#include <string.h>
#include <stdio.h>

#include "algorithm/master.h"
#include "algorithm/blocks.h"
#include "algorithm/algorithm.h"
#include "algorithm/primitives/primitives.h"
#include "algorithm/primitives/queue.h"

typedef enum
{
    NEIGHBOUR_READY = 0,
    WORKING = 1,
    FINISHED = 2,
    NEIGHBOUR_DELAYED = 3
} State;
typedef struct
{
    int block_i;
    int block_j;
    int proc_id;
    State state;
} TracebackWorker;

void enqueue_ready_blocks(Queue *queue, BlockMap *map, MatrixBlock *block)
{
    int i = block->i;
    int j = block->j;
    int width = map->width;
    int height = map->height;

    if (i < (height - 1) && j < (width - 1))
    {
        MatrixBlock *diag = get_MatrixBlock(i + 1, j + 1, map);
        if (block_is_ready(diag, map))
        {
            load_dependencies(diag, map);
            enqueue(queue, *diag);
            printf("(master process) enqueued block (%d, %d) \n", diag->i, diag->j);
        }
    }

    if (j < (width - 1))
    {
        MatrixBlock *der = get_MatrixBlock(i + 1, j, map);
        if (block_is_ready(der, map))
        {
            load_dependencies(der, map);
            enqueue(queue, *der);
            printf("(master process) enqueued block (%d, %d) \n", der->i, der->j);
        }
    }

    if (i < (height - 1))
    {
        MatrixBlock *inf = get_MatrixBlock(i, j + 1, map);
        if (block_is_ready(inf, map))
        {
            load_dependencies(inf, map);
            enqueue(queue, *inf);
            printf("(master process) enqueued block (%d, %d) \n", inf->i, inf->j);
        }
    }
}

void enqueue_ready_blocks_traceback(Queue *queue, BlockMap *map, MatrixBlock *block)
{
    int i = block->i;
    int j = block->j;

    if ((i - 1 >= 0) && (j - 1 >= 0))
    {
        MatrixBlock *diag = get_MatrixBlock(i - 1, j - 1, map);
        if (block_is_ready(diag, map))
        {
            load_dependencies(diag, map);
            enqueue(queue, *diag);
            printf("(master process) enqueued block (%d, %d) \n", diag->i, diag->j);
        }
    }

    if ((j - 1) >= 0)
    {
        MatrixBlock *der = get_MatrixBlock(i, j - 1, map);
        if (block_is_ready(der, map))
        {
            load_dependencies(der, map);
            enqueue(queue, *der);
            printf("(master process) enqueued block (%d, %d) \n", der->i, der->j);
        }
    }

    if ((i - 1) >= 0)
    {
        MatrixBlock *inf = get_MatrixBlock(i - 1, j, map);
        if (block_is_ready(inf, map))
        {
            load_dependencies(inf, map);
            enqueue(queue, *inf);
            printf("(master process) enqueued block (%d, %d) \n", inf->i, inf->j);
        }
    }
}

void update_TracebackWorkers(TracebackWorker *traceback_workers, int block_i, int block_j, int proc_id, State state)
{
    traceback_workers[proc_id - 1].block_i = block_i;
    traceback_workers[proc_id - 1].block_j = block_j;
    traceback_workers[proc_id - 1].proc_id = proc_id;
    traceback_workers[proc_id - 1].state = state;
}

int get_TracebackWorker(TracebackWorker *traceback_workers, int block_i, int block_j)
{
    for (int i = 0; i < 4; i++)
    {
        if (traceback_workers[i].block_i == block_i && traceback_workers[i].block_j == block_j)
        {
            return traceback_workers[i].proc_id;
        }
    }
    return -1; // no se encontro el bloque
}

void update_Traceback(TracebackResult *traceback_msg, List *matched_seq1, List *matched_seq2)
{
    for (int j = traceback_msg->width - 1; j == 0; j--)
    {
        push(&matched_seq1, traceback_msg->matched_seq1[j]);
    }

    for (int i = traceback_msg->height - 1; i == 0; i--)
    {
        push(&matched_seq2, traceback_msg->matched_seq2[i]);
    }
}

MatrixBlock *get_NextBlockTraceback(BlockMap *map, TracebackResult *traceback_msg)
{
    int i = traceback_msg->block_i;
    int j = traceback_msg->block_j;

    if (traceback_msg->next_block == DIAG && (i - 1 >= 0) && (j - 1 >= 0))
    {
        return get_MatrixBlock(i - 1, j - 1, map);
    }
    else if (traceback_msg->next_block == UP && (i - 1 >= 0))
    {
        return get_MatrixBlock(i - 1, j, map);
    }
    else if (traceback_msg->next_block == LEFT && (j - 1 >= 0))
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
        block->max_cell.i = traceback_msg->next_starting_cell.i + block->height - 1;
        block->max_cell.j = traceback_msg->next_starting_cell.j + block->width - 1;
    }
    else if (traceback_msg->next_block == UP)
    {
        block->max_cell.i = traceback_msg->next_starting_cell.i + block->height - 1;
        block->max_cell.j = traceback_msg->next_starting_cell.j;
    }
    else if (traceback_msg->next_block == LEFT)
    {
        block->max_cell.i = traceback_msg->next_starting_cell.i;
        block->max_cell.j = traceback_msg->next_starting_cell.j + block->width - 1;
    }

    block->max_cell.max_score = traceback_msg->next_starting_cell.max_score;
}

void master(CharArray *seq1, CharArray *seq2)
{
    printf("(master process) initialized \n");
    // preparar sus estructuras de control, mapa de bloques, etc
    BlockMap *map = create_Map(seq1, seq2);
    Queue *queue = createQueue(max(seq1->length, seq2->length));

    int nro_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &nro_procs);
    bool *proc_available = malloc(nro_procs * sizeof(bool));
    for (int i = 1; i < nro_procs; i++)
    {
        proc_available[i] = true;
    }

    // solo se necesita 1 de cada para trabajar el master
    BlockParam *param_msg = create_blockParam();
    BlockResult *result_msg = create_blockResult();

    int cnxt_pid = 1;

    MatrixBlock *block = get_MatrixBlock(0, 0, map);
    // row and col of 0s
    for (int i = 0; i < BLOCK_WIDTH; i++)
    {
        block->row[i] = 0;
    }
    for (int i = 0; i < BLOCK_HEIGHT; i++)
    {
        block->col[i] = 0;
    }

    load_BlockParam(param_msg, block, seq1, seq2);

    printf("(master process) ready for distributing work \n");

    // int count = 0;
    // MPI_Request request;
    MPI_Status status;

    send_BlockParam(param_msg, cnxt_pid, TAG_BLOCK_PARAM);

    int working_procs = 1;

    while (true)
    {
        receive_BlockResult(result_msg, &cnxt_pid, &status);

        if (status.MPI_TAG == TAG_BLOCK_RESULT)
        {
            printf("(master process) received result for block (%d, %d) from process %d \n", result_msg->block.i, result_msg->block.j, cnxt_pid);

            // actualizo el bloque en el mapa
            update_BlockMap(result_msg->block, map);

            // agrego a la cola los nuevos bloques a procesar
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
                    printf("(master process) popped block (%d, %d): sent to process %d \n", block->i, block->j, i);
                    load_BlockParam(param_msg, block, seq1, seq2);
                    send_BlockParam(param_msg, i, TAG_BLOCK_PARAM);
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

    // arranco con el traceback
    List *matched_seq1 = NULL;
    List *matched_seq2 = NULL;

    TracebackResult *traceback_msg = create_tracebackResult();

    // arreglo donde guardo el estado actual de los 4 workers
    TracebackWorker traceback_workers[4];

    // bloque donde empieza el traceback, que es el que tiene el max score
    block = get_TracebackStartingBlock(map);

    // en este caso el starting_cell es el max_cell guardado en el bloque
    load_BlockParam(param_msg, block, seq1, seq2);

    // mando el bloque a trabajar con el traceback
    send_BlockParam(param_msg, 1, TAG_TRACEBACK_FIRST_RUN);

    // actualizo el estado del worker
    update_TracebackWorkers(traceback_workers, block->i, block->j, 1, WORKING);

    working_procs = 1;

    // encolo los otros 3 bloques
    enqueue_ready_blocks_traceback(queue, map, block);

    for (int i = 2; i < 5; i++)
    {
        block = dequeue(queue);
        printf("(master process) popped block (%d, %d): sent to process %d \n", block->i, block->j, i);
        load_BlockParam(param_msg, block, seq1, seq2);

        // mando el bloque vecino para que este listo por adelantado
        send_BlockParam(param_msg, i, TAG_TRACEBACK_NEIGHBOUR);
        update_TracebackWorkers(traceback_workers, block->i, block->j, i, WORKING);
        working_procs++;
    }

    while (true)
    {
        receive_TracebackResult(traceback_msg, &cnxt_pid, &status);
        if (status.MPI_TAG == TAG_TRACEBACK_NEIGHBOUR_READY)
        {
            // actualizo el estado del worker que se comunico
            printf("(master process) received traceback neighbour ready for block (%d, %d) from process %d \n", traceback_msg->block_i, traceback_msg->block_j, cnxt_pid);
            update_TracebackWorkers(traceback_workers, traceback_msg->block_i, traceback_msg->block_j, cnxt_pid, NEIGHBOUR_READY);
            working_procs--;
            // cuando se agregaron nuevamente bloques a la cola a lo mejor un worker no habia terminado con el anterior
            // o sea va una iteracion atrasado y debe ponerse al dia y ejecutar el bloque que ahora le corresponde
            if (!isEmpty(queue) && traceback_workers[cnxt_pid - 1].state == NEIGHBOUR_DELAYED)
            {
                block = dequeue(queue);
                printf("(master process) popped block (%d, %d): sent to process %d \n", block->i, block->j, cnxt_pid);
                load_BlockParam(param_msg, block, seq1, seq2);
                send_BlockParam(param_msg, cnxt_pid, TAG_TRACEBACK_NEIGHBOUR);
                update_TracebackWorkers(traceback_workers, block->i, block->j, cnxt_pid, WORKING);
                working_procs++;
            }
        }

        if (status.MPI_TAG == TAG_TRACEBACK_RESULT)
        {
            // actualizo el estado del worker que se comunico
            printf("(master process) received traceback block result (%d, %d) from process %d \n", traceback_msg->block_i, traceback_msg->block_j, cnxt_pid);
            update_TracebackWorkers(traceback_workers, traceback_msg->block_i, traceback_msg->block_j, cnxt_pid, FINISHED);
            working_procs--;

            // actualizo las secuencias encontradas en el traceback
            update_Traceback(traceback_msg, matched_seq1, matched_seq2);

            // obtengo el siguiente bloque para el traceback
            block = get_NextBlockTraceback(map, traceback_msg);

            // si no hay siguiente bloque para el traceback es porque termino
            if (block == NULL)
            {
                printf("(master process) traceback completed \n");
                break;
            }
            // el traceback arranca en una celda que no es la guardada en el map
            // cargo el starting_cell en el bloque para que el slave arranque desde ahi
            load_NextStartingCell(traceback_msg, block);

            // veo que worker estaba trabajando por adelanto el siguiente bloque del traceback
            int proc_id = get_TracebackWorker(traceback_workers, block->i, block->j);

            // espero a que el worker lo finalice si no lo ha hecho aun
            while (traceback_workers[proc_id - 1].state != NEIGHBOUR_READY)
            {
                receive_TracebackResult(traceback_msg, &cnxt_pid, &status);
                if (status.MPI_TAG == TAG_TRACEBACK_NEIGHBOUR_READY)
                {
                    update_TracebackWorkers(traceback_workers, traceback_msg->block_i, traceback_msg->block_j, cnxt_pid, NEIGHBOUR_READY);
                    working_procs--;
                }
            }

            // encolo los bloques vecinos para que se vayan recalculando en paralelo
            enqueue_ready_blocks_traceback(queue, map, block);

            // envio a que se empiece a correr el traceback sobre el bloque que ya va a estar calculado
            printf("(master process) popped block (%d, %d): sent to process %d \n", block->i, block->j, proc_id);
            load_BlockParam(param_msg, block, seq1, seq2);
            send_BlockParam(param_msg, proc_id, TAG_TRACEBACK_RUN);
            update_TracebackWorkers(traceback_workers, block->i, block->j, proc_id, WORKING);
            working_procs++;

            int i = 1;
            while (i < 5)
            {
                // solo se manda a workers que no estan ejecutando (esten o no atrasados)
                if (traceback_workers[i - 1].state != WORKING || traceback_workers[i - 1].state != NEIGHBOUR_DELAYED)
                {
                    if (isEmpty(queue))
                        break;
                    block = dequeue(queue);
                    printf("(master process) popped block (%d, %d): sent to process %d \n", block->i, block->j, i);
                    load_BlockParam(param_msg, block, seq1, seq2);
                    send_BlockParam(param_msg, i, TAG_TRACEBACK_NEIGHBOUR);
                    update_TracebackWorkers(traceback_workers, block->i, block->j, i, WORKING);
                    working_procs++;
                    i++;
                }
                // si el proceso esta trabajando y no es el que esta haciendo el traceback localmente -> es porque esta atrasado
                if (traceback_workers[i - 1].state == WORKING && i != proc_id)
                {
                    traceback_workers[i - 1].state = NEIGHBOUR_DELAYED;
                }
            }

            if (isEmpty(queue) && working_procs == 0)
            {
                break;
            }
        }
    }
    // print_block_map(map, seq1, seq2);

    // terminar slaves para que liberen su memoria y terminen
    for (int i = 1; i < nro_procs; i++)
    {
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
    free_BlockParam(param_msg);
    free_BlockResult(result_msg);
    free_TracebackResult(traceback_msg);
}
