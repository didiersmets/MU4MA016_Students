#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/circular_buffer_queue.h"

bool is_empty(const struct Queue *q)
{
    return q->length == 0;
}

size_t queue_length(const struct Queue *q)
{
    return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity)
{
    struct Queue *q = malloc(sizeof(struct Queue));
    assert(q != NULL);

    q->data = malloc(elem_size * capacity);
    assert(q->data != NULL);

    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->elem_size = elem_size;
    return q;
}

void queue_dispose(struct Queue *q)
{
    if (!q)
        return;
    free(q->data);
    free(q);
}

static void enlarge_queue_capacity(struct Queue *q)
{
    size_t new_capacity = q->capacity * 2;
    void *new_data = malloc(new_capacity * q->elem_size);
    assert(new_data != NULL);

    for (size_t i = 0; i < q->length; i++)
    {
        size_t old_index = (q->front + i) % q->capacity;
        void *src = (char *)q->data + old_index * q->elem_size;
        void *dst = (char *)new_data + i * q->elem_size;
        memcpy(dst, src, q->elem_size);
    }

    free(q->data);
    q->data = new_data;
    q->capacity = new_capacity;
    q->front = 0;
}

void queue_enqueue(struct Queue *q, const void *src)
{
    if (q->length == q->capacity)
    {
        enlarge_queue_capacity(q);
    }

    size_t pos = (q->front + q->length) % q->capacity;
    void *dst = (char *)q->data + pos * q->elem_size;
    memcpy(dst, src, q->elem_size);

    q->length++;
}

void queue_dequeue(struct Queue *q, void *dest)
{
    assert(q->length > 0);

    void *src = (char *)q->data + q->front * q->elem_size;
    if (dest != NULL)
    {
        memcpy(dest, src, q->elem_size);
    }

    q->front = (q->front + 1) % q->capacity;
    q->length--;
}
