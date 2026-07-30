#include "algorithm/sequential.h"
#include "algorithm/common.h"

void sequential_init(bool load_checkpoint)
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

    matched_seq1 = NULL;
    matched_seq2 = NULL;

    cell = malloc(sizeof(MatrixCell));
    matrix = create_block(BLOCK_WIDTH + 1, BLOCK_HEIGHT + 1);
    if (matrix == NULL)
    {
        // TODO precisa una mejor solucion
        logging(1, "failed to allocate matrix block\n");
        exit(EXIT_FAILURE);
    }

    if (!load_checkpoint)
    {
        checkpoint = create_checkpoint_file(CHECKPOINT_FILE_PATH);
        block = get_MatrixBlock(0, 0, map);
        load_dependencies(block, map);

        enqueue(queue, block);
    }
    else
    {
        checkpoint = open_checkpoint_file(CHECKPOINT_FILE_PATH);
        wavefront_number = load_from_checkpoint(checkpoint, map);

        // encolo los bloques que estan para ejecutar
        for (int i = 0; i < map->height && i <= wavefront_number; i++)
        {
            int j = wavefront_number - i;
            if (j >= 0 && j < map->width)
            {
                block = get_MatrixBlock(i, j, map);
                enqueue_ready_blocks(queue, map, block);
            }
        }
    }
}

void sequential_completion()
{
    CharArray *completion_seq1 = malloc(sizeof(CharArray));
    CharArray *completion_seq2 = malloc(sizeof(CharArray));
    while (true)
    {
        auto_save_checkpoint(&wavefront_number, checkpoint, map);

        if (isEmpty(queue))
            break;
        block = dequeue(queue);

        load_dependencies(block, map);

        load_BlockParam(param_msg, block, seq1, seq2);

        completion_seq1->data = param_msg->seq1;
        completion_seq1->length = param_msg->block.width;
        completion_seq2->data = param_msg->seq2;
        completion_seq2->length = param_msg->block.height;

        load_block(matrix, &param_msg->block);
        complete_block(matrix, cell, completion_seq1, completion_seq2);
        load_blockResult(result_msg, matrix, cell, param_msg);

        if (result_msg->result.max_score > max_score_block->max_cell.max_score)
        {
            max_score_block->i = result_msg->block.i;
            max_score_block->j = result_msg->block.j;
            max_score_block->max_cell.i = result_msg->result.i;
            max_score_block->max_cell.j = result_msg->result.j;
            max_score_block->max_cell.max_score = result_msg->result.max_score;
        }

        update_BlockMap(result_msg, map);
        enqueue_ready_blocks(queue, map, &result_msg->block);
    }
    free(completion_seq1);
    free(completion_seq2);
}

void sequential_traceback()
{
    CharArray *traceback_seq1 = malloc(sizeof(CharArray));
    CharArray *traceback_seq2 = malloc(sizeof(CharArray));

    // traceback
    char *calculated_seq1 = calloc(BLOCK_WIDTH + BLOCK_HEIGHT, sizeof(char));
    char *calculated_seq2 = calloc(BLOCK_WIDTH + BLOCK_HEIGHT, sizeof(char));
    Direction next_block = 0;
    int traceback_length = 0;

    traceback_msg = create_tracebackResult();
    block = get_MatrixBlock(max_score_block->i, max_score_block->j, map);
    while (true)
    {
        load_dependencies(block, map);
        load_BlockParam(param_msg, block, seq1, seq2);

        traceback_seq1->data = param_msg->seq1;
        traceback_seq1->length = param_msg->block.width;
        traceback_seq2->data = param_msg->seq2;
        traceback_seq2->length = param_msg->block.height;

        load_block(matrix, &param_msg->block);
        complete_block(matrix, cell, traceback_seq1, traceback_seq2);

        // es la celda por la que debemos arrancar el traceback en este bloque
        cell->i = param_msg->block.max_cell.i;
        cell->j = param_msg->block.max_cell.j;
        cell->max_score = param_msg->block.max_cell.max_score;

        next_block = calculate_traceback_block(calculated_seq1, calculated_seq2, matrix, cell, &traceback_length, traceback_seq1->data, traceback_seq2->data);

        load_tracebackResult(traceback_msg, cell, next_block, param_msg, traceback_length, calculated_seq1, calculated_seq2);

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
    }

    free(traceback_seq1);
    free(traceback_seq2);
    free(calculated_seq1);
    free(calculated_seq2);
}

void sequential(CharArray *sequence1, CharArray *sequence2, bool load_checkpoint)
{
    seq1 = sequence1;
    seq2 = sequence2;
    sequential_init(load_checkpoint);

    sequential_completion();

    sequential_traceback();

    save_list(matched_seq1, "./data/temp/matched_seq1.txt");
    save_list(matched_seq2, "./data/temp/matched_seq2.txt");

    free(map);
    free(queue);
    free_BlockParam(param_msg);
    free_BlockResult(result_msg);
    free_TracebackResult(traceback_msg);
    free_list(matched_seq1);
    free_list(matched_seq2);
    free_block(matrix);
    free(cell);
}
