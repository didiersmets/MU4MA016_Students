#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Queue {
    size_t front;
    size_t length;
    size_t capacity;
    size_t elem_size;
    void *data;
};

bool is_empty(const struct Queue *q) {
    return q->length == 0;
}

size_t queue_length(const struct Queue *q) {
    return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity) {
    struct Queue *q = malloc(sizeof(struct Queue));
    if (!q) return NULL;

    q->data = malloc(elem_size * capacity);
    if (!q->data) {
        free(q);
        return NULL;
    }

    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->elem_size = elem_size;

    return q;
}

void queue_dispose(struct Queue *q) {
    if (!q) return;
    free(q->data);
    free(q);
}

static bool enlarge_queue_capacity(struct Queue *q) {
    size_t new_capacity = q->capacity * 2;
    void *new_data = malloc(new_capacity * q->elem_size);
    if (!new_data) return false;

    for (size_t i = 0; i < q->length; ++i) {
        size_t old_index = (q->front + i) % q->capacity;
        void *src = (char *)q->data + old_index * q->elem_size;
        void *dst = (char *)new_data + i * q->elem_size;
        memcpy(dst, src, q->elem_size);
    }

    free(q->data);
    q->data = new_data;
    q->capacity = new_capacity;
    q->front = 0;

    return true;
}

bool queue_enqueue(struct Queue *q, const void *src) {
    if (q->length == q->capacity) {
        enlarge_queue_capacity(q);

        return false;
    }

    size_t index = (q->front + q->length) % q->capacity;
    void *target = (char *)q->data + index * q->elem_size;
    memcpy(target, src, q->elem_size);
    q->length++;

    return true;
}

bool queue_dequeue(struct Queue *q, void *dest) {
    if (q->length == 0) return false;

    void *source = (char *)q->data + q->front * q->elem_size;
    memcpy(dest, source, q->elem_size);

    q->front = (q->front + 1) % q->capacity;
    q->length--;

    return true;
}