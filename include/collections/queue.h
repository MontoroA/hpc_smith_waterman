#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdint.h>

#include "algorithm/blocks.h"

typedef struct
{
    MatrixBlock **items;
    uint32_t front;
    uint32_t rear;
    uint32_t size;
    uint32_t count;
} Queue;

// Function declarations for queue operations
Queue *createQueue(uint32_t size);
bool isEmpty(Queue *q);
bool isFull(Queue *q);
bool enqueue(Queue *q, MatrixBlock *value);
MatrixBlock *dequeue(Queue *q);
void freeQueue(Queue *q);

#endif