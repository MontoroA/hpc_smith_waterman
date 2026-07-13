#ifndef ALGORITHM_H
#define ALGORITHM_H


#include "primitives/primitives.h"

// matrix apunta al comienzo del bloque. Los seqs apuntan a las subsecuencias, limitadas por su length correspondiente
MatrixCell* complete_block(int* matrix, CharArray* seq1, CharArray* seq2);

void traceback(int* matrix, MatrixCell* entry, CharArray* sequence1, CharArray* sequence2);

#endif