#include <stdlib.h>

#include "collections/queue.h"

Queue* createQueue(int size)    
{
    if (size <= 0) {
        return NULL;
    }

    Queue *q = (Queue*) malloc(sizeof(Queue));
    if (!q) {
        return NULL;
    }

    q->items = (MatrixBlock *)malloc(size * sizeof(MatrixBlock));
    if (!q->items) {
        free(q);
        return NULL;
    }
    q->front = -1;
    q->rear = -1;
    q->size = size;
    return q;
}



bool isEmpty(Queue *q)
{
    return (q->front == -1);
}

bool isFull(Queue *q)
{
    return (((q->rear + 1) % q->size) == q->front);
}


bool enqueue(Queue *q, MatrixBlock value)
{
    if (isFull(q)) {
        return false;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % q->size;
    q->items[q->rear] = value;
    return true;
}


MatrixBlock* dequeue(Queue *q){
    if (isEmpty(q)) {
        return (MatrixBlock*)NULL; // Queue is empty
    }

    MatrixBlock* value = &q->items[q->front];

    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % q->size;
    }

    return value;
}

void freeQueue(Queue *q) {
    if (q) {
        free(q->items);
        free(q);
    }
}