#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#include "algorithm/blocks.h"

typedef struct {
    MatrixBlock *items;
    int front;
    int rear;
    int size;
} Queue;

// Function declarations for queue operations
Queue* createQueue(int size);
bool isEmpty(Queue *q);
bool isFull(Queue *q);
bool enqueue(Queue *q, MatrixBlock value);
MatrixBlock* dequeue(Queue *q);
void freeQueue(Queue *q);



#endif