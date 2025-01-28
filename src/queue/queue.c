#include "queue.h"

#include <string.h>

#define QUEUE_CAPACITY 1024

Queue queue_create(void)
{
    Queue q = { .index = 0 };
    return q;
}

void queue_enqueue(Queue *q, int value, bool *error_occured)
{
    if (q->index >= QUEUE_CAPACITY)
    {
        *error_occured = true;
        return;
    }

    q->data[q->index++] = value;
}

int queue_dequeue(Queue *q, bool *error_occured)
{
    if (q->index == 0)
    {
        *error_occured = true;
        return 0;
    }

    int value = q->data[0];

    // Shift elements to the left.
    memmove(q->data, q->data + 1, (q->index - 1) * sizeof(int));

    q->index--;
    return value;
}

bool queue_is_empty(Queue *q)
{
    return q->index == 0;
}
