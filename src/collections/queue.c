#include <stdlib.h>

#include "collections/queue.h"

Queue *createQueue(uint32_t size)
{
    if (size <= 0)
    {
        return NULL;
    }

    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (!q)
    {
        return NULL;
    }

    q->items = (MatrixBlock **)malloc(size * sizeof(MatrixBlock*));
    if (!q->items)
    {
        free(q);
        return NULL;
    }
    q->front = -1;
    q->rear = -1;
    q->size = size;
    q->count = 0;
    return q;
}

bool isEmpty(Queue *q)
{
    return (q->count == 0);
}

bool isFull(Queue *q)
{
    return (q->count == q->size);
}

bool enqueue(Queue *q, MatrixBlock *value)
{
    if (isFull(q))
    {
        return false;
    }
    if (isEmpty(q))
    {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % q->size;
    q->items[q->rear] = value;
    q->count++;
    value->is_queued = true;
    return true;
}

MatrixBlock *dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        return (MatrixBlock *)NULL; // Queue is empty
    }

    MatrixBlock *value = q->items[q->front];

    if (q->front == q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
    else
    {
        q->front = (q->front + 1) % q->size;
    }
    q->count--;
    value->is_queued = false;
    return value;
}

void freeQueue(Queue *q)
{
    if (q)
    {
        free(q->items);
        free(q);
    }
}