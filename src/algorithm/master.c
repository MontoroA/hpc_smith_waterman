#include "algorithm/master.h"
#include "algorithm/common.h"

void init(bool load_checkpoint)
{
    logging(MASTER_RANK, "initialized\n");
    map = create_Map(seq1, seq2);
    queue = createQueue(map->width * map->height);
    if (queue == NULL)
    {
        logging(MASTER_RANK, "failed to allocate work queue\n");
        exit(EXIT_FAILURE);
    }
    result_msg = create_blockResult();
    param_msg = create_blockParam();

    max_score_block = malloc(sizeof(MatrixBlock));
    max_score_block->i = 0;
    max_score_block->j = 0;
    max_score_block->max_cell.max_score = 0;

    MPI_Comm_size(MPI_COMM_WORLD, &nro_procs);
    proc_available = malloc(nro_procs * sizeof(bool));
    for (int i = 1; i < nro_procs; i++)
    {
        proc_available[i] = true;
    }

    matched_seq1 = NULL;
    matched_seq2 = NULL;

    logging(MASTER_RANK, "ready for distributing work\n");

    if (!load_checkpoint)
    {
        checkpoint = create_checkpoint_file(CHECKPOINT_FILE_PATH);
        block = get_MatrixBlock(0, 0, map);
        load_dependencies(block, map);

        load_BlockParam(param_msg, block, seq1, seq2);

        cnxt_pid = 1;
        working_procs = 1;

        send_BlockParam(param_msg, cnxt_pid, TAG_BLOCK_PARAM);
    }
    else
    {
        checkpoint = open_checkpoint_file(CHECKPOINT_FILE_PATH);
        wavefront_number = load_from_checkpoint(checkpoint, map);

        // encolo los bloques que estan para ejecutar
        for (uint32_t i = 0; i < map->height && i <= wavefront_number; i++)
        {
            uint32_t j = wavefront_number - i;
            if (j < map->width) // && j >= 0
            {
                block = get_MatrixBlock(i, j, map);
                enqueue_ready_blocks(queue, map, block);
            }
        }

        working_procs = 0;

        for (int i = 1; i < nro_procs; i++)
        {
            if (proc_available[i])
            {
                if (isEmpty(queue))
                    break;
                block = dequeue(queue);
                logging(MASTER_RANK, "popped block (%d, %d): sent to process %d\n", block->i, block->j, i);
                load_BlockParam(param_msg, block, seq1, seq2);
                send_BlockParam(param_msg, i, TAG_BLOCK_PARAM);
                proc_available[i] = false;
                working_procs++;
            }
        }
    }
}

void completion()
{
    while (true)
    {
        auto_save_checkpoint(&wavefront_number, checkpoint, map);

        receive_BlockResult(result_msg, &status);
        cnxt_pid = status.MPI_SOURCE;
        logging(MASTER_RANK, "received result for block (%d, %d) from process %d\n", result_msg->block.i, result_msg->block.j, cnxt_pid);
        if (status.MPI_TAG == TAG_BLOCK_RESULT)
        {
            if (result_msg->result.max_score > max_score_block->max_cell.max_score)
            {
                max_score_block->i = result_msg->block.i;
                max_score_block->j = result_msg->block.j;
                max_score_block->max_cell.i = result_msg->result.i;
                max_score_block->max_cell.j = result_msg->result.j;
                max_score_block->max_cell.max_score = result_msg->result.max_score;
                logging(MASTER_RANK, "New max score block (%d, %d) with max score %d\n", max_score_block->i, max_score_block->j, max_score_block->max_cell.max_score);
            }
            update_BlockMap(result_msg, map);
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
                    logging(MASTER_RANK, "popped block (%d, %d): sent to process %d\n", block->i, block->j, i);
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
}

void traceback()
{
    traceback_msg = create_tracebackResult();
    block = get_MatrixBlock(max_score_block->i, max_score_block->j, map);

    load_dependencies(block, map);
    load_BlockParam(param_msg, block, seq1, seq2);
    send_BlockParam(param_msg, 1, TAG_TRACEBACK_RUN);
    logging(MASTER_RANK, "block (%d, %d): sent to process traceback %d \n", block->i, block->j, 1);

    working_procs = 1;

    while (true)
    {
        receive_TracebackResult(traceback_msg, &cnxt_pid, &status);
        working_procs--;
        if (status.MPI_TAG == TAG_TRACEBACK_RESULT)
        {
            logging(MASTER_RANK, "received traceback block result (%d, %d) from process %d \n", traceback_msg->block_i, traceback_msg->block_j, cnxt_pid);

            // actualizo las secuencias encontradas en el traceback
            update_Traceback(traceback_msg, &matched_seq1, &matched_seq2);

            // obtengo el siguiente bloque para el traceback
            block = get_NextBlockTraceback(map, traceback_msg);

            // si no hay siguiente bloque para el traceback es porque termino
            if (block == NULL)
            {
                logging(MASTER_RANK, "traceback completed \n");
                break;
            }
            // el traceback arranca en una celda que no es la guardada en el map
            // cargo el starting_cell en el bloque para que el slave arranque desde ahi
            load_NextStartingCell(traceback_msg, block);

            load_dependencies(block, map);
            // envio a que se empiece a correr el traceback sobre el bloque que ya va a estar calculado
            logging(MASTER_RANK, "block (%d, %d): sent to process traceback %d \n", block->i, block->j, 1);
            load_BlockParam(param_msg, block, seq1, seq2);
            send_BlockParam(param_msg, 1, TAG_TRACEBACK_RUN);
            working_procs++;
        }
    }
}

SWAReport *master(CharArray *sequence1, CharArray *sequence2, bool load_checkpoint)
{
    seq1 = sequence1;
    seq2 = sequence2;

    init(load_checkpoint);
    completion();
    traceback();

    for (int i = 1; i < nro_procs; i++)
    {
        MPI_Send(NULL, 0, MPI_BYTE, i, TAG_TERMINATE, MPI_COMM_WORLD);
    }

    SWAReport *report = malloc(sizeof(SWAReport));
    report->matched_seq1 = matched_seq1;
    report->matched_seq2 = matched_seq2;

    free(map);
    free(proc_available);
    freeQueue(queue);
    free_BlockParam(param_msg);
    free_BlockResult(result_msg);
    free_TracebackResult(traceback_msg);
    return report;
}
