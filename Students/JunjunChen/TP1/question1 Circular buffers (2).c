// question 1 Circular buffers (2)
MU4MA016_Students/
└─ TP1/
   ├─ include/
   │   └─ circular_buffer_queue.h
   └─ src/
       ├─ circular_buffer_queue.c
       └─ test_queue.c

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "circular_buffer_queue.h"

static void enlarge_queue_capacity(struct Queue *q) {
    if (q->capacity == 0) {
        q->capacity = 1;
    }
    size_t old_cap = q->capacity;
    size_t new_cap = old_cap * 2;

    void *new_data = malloc(new_cap * q->elem_size);
    if (!new_data) {
        fprintf(stderr, "enlarge_queue_capacity: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < q->length; ++i) {
        size_t from_idx = (q->front + i) % old_cap;
        void *from = (char*)q->data + from_idx * q->elem_size;
        void *to   = (char*)new_data + i * q->elem_size;
        memcpy(to, from, q->elem_size);
    }

    free(q->data);
    q->data = new_data;
    q->capacity = new_cap;
    q->front = 0;
}

//initialization
struct Queue *queue_init(size_t elem_size, size_t capacity) {
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    if (!q) {
        fprintf(stderr, "queue_init: malloc Queue failed\n");
        exit(EXIT_FAILURE);
    }
    q->front = 0;
    q->length = 0;
    q->capacity = (capacity == 0 ? 1 : capacity);
    q->elem_size = elem_size;
    q->data = malloc(q->capacity * q->elem_size);
    if (!q->data) {
        fprintf(stderr, "queue_init: malloc data failed\n");
        free(q);
        exit(EXIT_FAILURE);
    }
    return q;
}

//enqueue
void queue_enqueue(struct Queue *q, const void *src) {
    if (q->length == q->capacity) {
        enlarge_queue_capacity(q);
    }
    size_t tail = (q->front + q->length) % q->capacity;
    void *dest = (char*)q->data + tail * q->elem_size;
    memcpy(dest, src, q->elem_size);
    q->length += 1;
}

//dequeue
void queue_dequeue(struct Queue *q, void *dest) {
    if (q->length == 0) {
        return;
    }
    void *src = (char*)q->data + q->front * q->elem_size;
    memcpy(dest, src, q->elem_size);
    q->front = (q->front + 1) % q->capacity;
    q->length -= 1;
}
