#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "circular_buffer_queue.h"  // chemin d'include via -I include

static void enlarge_queue_capacity(struct Queue *q) {
    // Double la capacité quand la file est pleine.
    size_t new_cap = (q->capacity == 0) ? 1 : (q->capacity * 2);
    void *new_data = malloc(new_cap * q->elem_size);
    if (!new_data) {
        fprintf(stderr, "enlarge_queue_capacity: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    // Re-copier les 'length' éléments dans l'ordre logique en partant de 0
    // Éléments actuels aux indices: front, front+1, ..., front+length-1 (mod capacity)
    for (size_t k = 0; k < q->length; ++k) {
        size_t old_idx = (q->front + k) % q->capacity;
        void *src = (char*)q->data + old_idx * q->elem_size;
        void *dst = (char*)new_data + k * q->elem_size;
        memcpy(dst, src, q->elem_size);
    }

    free(q->data);
    q->data = new_data;
    q->capacity = new_cap;
    q->front = 0;  // on réaligne le front au début
}

bool is_empty(const struct Queue *q) {
    return q->length == 0;
}

size_t queue_length(const struct Queue *q) {
    return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity) {
    if (elem_size == 0) {
        fprintf(stderr, "queue_init: elem_size must be > 0\n");
        return NULL;
    }
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    if (!q) return NULL;

    if (capacity == 0) capacity = 1; // capacité minimale de 1
    q->data = malloc(capacity * elem_size);
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
    q->data = NULL;
    free(q);
}

void queue_enqueue(struct Queue *q, const void *src) {
    if (q->length == q->capacity) {
        enlarge_queue_capacity(q);
    }
    // Position d’insertion = (front + length) mod capacity
    size_t tail = (q->front + q->length) % q->capacity;
    void *dst = (char*)q->data + tail * q->elem_size;
    memcpy(dst, src, q->elem_size);
    q->length += 1;
}

void queue_dequeue(struct Queue *q, void *dest) {
    if (is_empty(q)) {
        fprintf(stderr, "queue_dequeue: empty queue\n");
        exit(EXIT_FAILURE);
    }
    void *src = (char*)q->data + q->front * q->elem_size;
    if (dest) {
        memcpy(dest, src, q->elem_size);
    }
    // Avancer le front circulairement
    q->front = (q->front + 1) % q->capacity;
    q->length -= 1;
}
