#include "circular_buffer_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void enlarge_queue_capacity(struct Queue *q) {
    size_t new_capacity = q->capacity * 2;
    void *new_data = malloc(q->elem_size * new_capacity);

    for (size_t i = 0; i < q->length; i++) {
        size_t index = (q->front + i) % q->capacity;
        void *source = (char *)q->data + (index * q->elem_size);
        void *target = (char *)new_data + (i * q->elem_size);
        memcpy(target, source, q->elem_size);
    }

    free(q->data);
    q->data = new_data;
    q->capacity = new_capacity;
    q->front = 0;
}

struct Queue *queue_init(size_t elem_size, size_t capacity) {
    struct Queue *q = malloc(sizeof(struct Queue));
    q->data = malloc(elem_size * capacity);

    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->elem_size = elem_size;

    return q;
}

bool is_empty(const struct Queue *q) {
    return q->length == 0;
}

size_t queue_length(const struct Queue *q) {
    return q->length;
}

void queue_dispose(struct Queue *q) {
    free(q->data);
    free(q);
}

void queue_enqueue(struct Queue *q, const void *src) {
    if (q->length == q->capacity) {
        enlarge_queue_capacity(q);
    }

    size_t rear = (q->front + q->length) % q->capacity;
    void *target = (char *)q->data + (rear * q->elem_size);
    memcpy(target, src, q->elem_size);
    q->length++;
}

void queue_dequeue(struct Queue *q, void *dest) {
    if (is_empty(q)) {
        fprintf(stderr, "Error: Queue is empty. Cannot dequeue element.\n");
        return;
    }

    void *source = (char *)q->data + (q->front * q->elem_size);
    memcpy(dest, source, q->elem_size);
    q->front = (q->front + 1) % q->capacity;
    q->length--;
}
