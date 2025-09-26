#include <stdbool.h>
#include <stddef.h> 
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>

#include "../include/circular_buffer_queue.h"

struct Queue *queue_init(size_t elem_size, size_t capacity){
    
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));

    q->data = malloc(elem_size*capacity);
    q->capacity = capacity;
    q->elem_size = elem_size;
    q->front = q->length=0;

    return 	q;
}

static void enlarge_queue_capacity(struct Queue *q){
    // Double the capacity and copy elements from old buffer to new buffer
    size_t new_capacity = q->capacity * 2;
    void *new_data = malloc(q->elem_size * new_capacity);
    for (size_t i = 0; i < q->length; i++) {
        size_t old_index = (q->front + i) % q->capacity;
        size_t new_index = i;
        void *old_elem = (char *)q->data + (old_index * q->elem_size);
        void *new_elem = (char *)new_data + (new_index * q->elem_size);
        memcpy(new_elem, old_elem, q->elem_size);
    }

    free(q->data);
    q->data = new_data;
    q->capacity = new_capacity;
    q->front = 0;
}

void queue_dispose(struct Queue *q){
    free(q->data);
    free(q);
}

void queue_enqueue(struct Queue *q, const void *src){
    // Check if the queue is full and enlarge if necessary
    if (q->length == q->capacity) {
        enlarge_queue_capacity(q);
    }
    size_t index = (q->front + q->length) % q->capacity;
    void *dest = (char *)q->data + (index * q->elem_size);
    memcpy(dest, src, q->elem_size);
    q->length++;
}


void queue_dequeue(struct Queue *q, void *dest)
{
    // Check if the queue is empty
    if (is_empty(q)) {
        printf("Queue is already empty.\n");
        return ;
    }
    size_t index = q->front;
    void *src = (char *)q->data + (index * q->elem_size);
    memcpy(dest, src, q->elem_size);
    q->front = (q->front + 1) % q->capacity;
    q->length--;
    
}

int get_length(struct Queue *q){
    return q->length;
}

bool is_empty(const struct Queue *q){
    return q->length == 0;
}