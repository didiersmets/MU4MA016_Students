#include <stdbool.h>
#include <stddef.h> 
#include <stdlib.h>
#include <string.h>

#include "circular_buffer_queue.h"

bool is_empty(const struct Queue *q) {
    return q->length == 0;
}

size_t queue_length(const struct Queue *q) {
    return q->length;
}

int queue_init(struct Queue *q, size_t elem_size, size_t capacity) {
    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->elem_size = elem_size;
    q->data = malloc(elem_size * capacity);
    if (q->data == NULL) {
        return -1;
    }
    return 0;
}

void queue_dispose(struct Queue *q) {
    free(q->data);
}

void queue_enqueue(struct Queue *q, const void *src) {
    if (q->length == q->capacity) {
        enlarge_queue_capacity(q);
    }
    size_t back = (q->front + q->length) % q->capacity;
    memcpy(q->data + back * q->elem_size, src, q->elem_size);
    q->length++;
}

void queue_dequeue(struct Queue *q, void *dest) {
    if (q->length == 0) {
        return;
    }
    memcpy(dest, q->data + q->front * q->elem_size, q->elem_size);
    q->front = (q->front + 1) % q->capacity;
    q->length--;
}

static void enlarge_queue_capacity(struct Queue *q) {
    size_t new_capacity = q->capacity * 2;
    void *new_data = malloc(q->elem_size * new_capacity);
    if (new_data == NULL) {
        return;
    }
    for (size_t i = 0; i < q->length; i++) {
        size_t j = (q->front + i) % q->capacity;
        memcpy(new_data + i * q->elem_size, q->data + j * q->elem_size, q->elem_size);
    }
    free(q->data);
    q->data = new_data;
    q->front = 0;
    q->capacity = new_capacity;
}