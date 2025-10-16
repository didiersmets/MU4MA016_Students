#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#include <stdbool.h> 
//#include <stddef.h>
#include <string.h>
#include "../include/circular_buffer_queue.h" 

bool is_empty(const struct Queue *q){
    assert(q != NULL); 
    return (q->length != 0);
};

size_t queue_length(const struct Queue *q){
    assert(q != NULL); 
    return (q->length);
};

struct Queue *queue_init(size_t elem_size, size_t capacity){
    struct Queue *q = malloc(sizeof(struct Queue)); // allocate space in the heap
    q->capacity = capacity;
    q->elem_size = elem_size;
    q->front = 0; // first element in the queue is index 0
    q->length = 0; // not 1 
    q->data = malloc(elem_size*capacity); // important, that was not allocated in the first malloc
    return q;
};

void queue_dispose(struct Queue *q){
    free(q->data);
    free(q);
    return;
};

static void enlarge_queue_capacity(struct Queue *q){
    if (q->capacity != 0){
        q->capacity = 2 * q->capacity; // geometrical (good complexity cf course notes)
    } else {
        q->capacity = 1; // not sure if that is wise
    }
    void *datacopy = q->data; // copy
    free(q->data); // to allocate the new capacity after
    q->data = malloc(q->elem_size * q->capacity);
    q->data = datacopy;
    return;
};

void queue_enqueue(struct Queue *q, const void *src){
    if (q->capacity <= q->length){
        enlarge_queue_capacity(q);
    };

    void *dest = (char*)q->data + ((q->front + q->length)%q->capacity)*q->elem_size; // so that we can do pointer arithmetics
    // %q->capacity is for the "circular" feature, to restart at the beginning if (q->front + q->length) is greater than the capacity
    memcpy(dest, src, q->elem_size);
    q->length += 1;
    return;
};

void queue_dequeue(struct Queue *q, void *dest){
    if (!q->length) {return;} 
    const void *src = (const char*)q->data + (q->front * q->elem_size); // of course not summing the q->length
    memcpy(dest, src, q->elem_size);
    q->front = (q->front + 1) % q->capacity;;
    q->length -= 1;
    return;
};