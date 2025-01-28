#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#define QUEUE_CAPACITY 2048

typedef struct Queue
{
    int index;
    int data[QUEUE_CAPACITY];
} Queue;

Queue queue_create(void);

void queue_enqueue(Queue *q, int value, bool *error_occured);

int queue_dequeue(Queue *q, bool *error_occured);

bool queue_is_empty(Queue *q);

#endif /* ! QUEUE_H */
