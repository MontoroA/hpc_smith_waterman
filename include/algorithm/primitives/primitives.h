#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdbool.h>

#include "utils/utils.h"

#define M       2                       // positive reward for similarity match
#define mu      10                      // negative reward for similarity mismatch
#define GAP_W   3                       // gap penalty constant
#define s(a,b)  (((a)==(b)) ? M : -mu)  // similarity function
#define W(k)    (-(GAP_W) * (k))        // gap penalty function. If linearity of this function is altered, check for comment "//assumes linearity"
#define min(a,b) (((a)<(b)) ? (a) : (b))
#define max(a,b) (((a)>(b)) ? (a) : (b))

typedef enum {
    UP = 0,
    DIAG = 1,
    LEFT = 2
} Direction;

typedef struct {
    int i;
    int j;
    int max_score;
} MatrixCell;

typedef struct {
    int i;
    int j;
} MatrixIndex;

typedef struct {
    bool* visited;
    int current_level;
} MatrixMap;

MatrixMap create_block_map(CharArray* seq1, CharArray* seq2);

void print_block_map(MatrixMap map, CharArray* seq1, CharArray* seq2);

MatrixIndex* get_unlocked_neighbors(MatrixIndex block, MatrixMap map);

#endif