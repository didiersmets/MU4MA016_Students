#include <stdbool.h>
#include <stddef.h> // for size_t
#include <string.h>  // pour memcpy
#include <stdio.h>
#include <stdlib.h>
#include "../include/circular_buffer_queue.h"


bool is_empty(const struct Queue *q){
	return q->length == 0;
};

size_t queue_length(const struct Queue *q){
	return q->length;
};

struct Queue *queue_init(size_t elem_size, size_t capacity){
	struct Queue *q = malloc(sizeof(struct Queue));
    if (!q) return NULL;

    q->data = malloc(elem_size * capacity);
    if (!q->data) {
        free(q);
        return NULL;
    }

    q->elem_size = elem_size;
    q->capacity = capacity;
    q->length = 0;
    q->front = 0;

    return q;
};

void queue_dispose(struct Queue *q){
	if (!q) return;
    free(q->data);
    free(q);
};

static void enlarge_queue_capacity(struct Queue * q ){
	size_t new_capacity = q->capacity * 2;
    void *new_data = malloc(new_capacity * q->elem_size);

    // recopie des éléments dans l’ordre
    for (size_t i = 0; i < q->length; i++) {
        size_t index = (q->front + i) % q->capacity;
        memcpy((char*)new_data + i * q->elem_size,
               (char*)q->data + index * q->elem_size,
               q->elem_size);
    }

    free(q->data);
    q->data = new_data;
    q->capacity = new_capacity;
    q->front = 0;
};

void queue_enqueue(struct Queue *q, const void *src){
	    if (q->length == q->capacity) {
        enlarge_queue_capacity(q);
    }

    size_t rear = (q->front + q->length) % q->capacity;
    memcpy((char*)q->data + rear * q->elem_size, src, q->elem_size);
    q->length++;
};

void queue_dequeue(struct Queue *q, void *dest){
	if (is_empty(q)) return;

    memcpy(dest, (char*)q->data + q->front * q->elem_size, q->elem_size);
    q->front = (q->front + 1) % q->capacity;
    q->length--;
};

