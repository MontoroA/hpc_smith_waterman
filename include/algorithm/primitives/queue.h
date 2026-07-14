#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#include "algorithm/primitives/primitives.h"

typedef struct {
    MatrixIndex *items;
    int front;
    int rear;
    int size;
} Queue;

// Function declarations for queue operations
Queue* createQueue(int size);
bool isEmpty(Queue *q);
bool isFull(Queue *q);
bool enqueue(Queue *q, MatrixIndex value);
MatrixIndex dequeue(Queue *q);



#endif