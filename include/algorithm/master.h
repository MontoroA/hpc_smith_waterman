#include "blocks.h"

void broadcast_sequences(int len1, int len2, char *seq1, char *seq2);

void load_start_message(BlockStartMessage *msg, int command, int index_x, int index_y,
                        int start_seq1, int start_seq2, int num_rows, int num_cols,
                        int *top_row, int *left_col, int prev_diag);

void send_start_message(BlockStartMessage *msg);

void receive_result_message(BlockResultMessage *msg);