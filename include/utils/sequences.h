#ifndef SEQUENCES_H
#define SEQUENCES_H

#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "collections/arrays.h"

#define MAX_BUFFER_SIZE 3000000 

typedef struct {
    CharArray* data;
    uint32_t start;
    uint32_t total_length;
    char* path;
} SequenceBuffer;

SequenceBuffer* load_Sequence(const char* path, const uint32_t start);

SequenceBuffer** execute_mode(int mode, char** params);

uint32_t count_files(const char *path);

bool buffer_contains(SequenceBuffer* buffer, uint32_t start, uint32_t length);

// Responsabilidad del llamador liberar la memoria del path
void free_SequenceBuffer(SequenceBuffer* buffer);

#endif