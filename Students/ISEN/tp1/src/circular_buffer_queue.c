#include "circular_buffer_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void enlarge_queue_capacity(struct Queue *q){
    //double capacity -> better than increasing it arithmetically
    void *A = malloc(2 * q->capacity * q->elem_size);
    //two cases
    //case 1: 
    if(q->front + q->length <= q->capacity){
        void *dest = A;
        const void *src = (char*)q->data + q->front * q->elem_size;
        size_t byte_size = q->length * q->elem_size;
        memcpy(dest, src, byte_size);
    }
    //case 2: 
    else{
        void *src1 = (char*)q->data + q->front * q->elem_size;
        void *src2 = (char*)q->data;   /*(char*) not necessary?!*/
        size_t first_part = (q->capacity - q->front) * q->elem_size; 
        void *dest1 = A;
        void *dest2 = (char*)A + first_part * q->elem_size;
        size_t snd_part = q->length * q->elem_size - first_part;
        memcpy(dest1, src1, first_part);
        memcpy(dest2, src2, snd_part);
    }
    free(q->data);
    q->data = A;
    q->capacity = 2 * q->capacity;
    q->front = 0;
};

bool is_empty(const struct Queue *q){
    return(q->length == 0);
};

size_t queue_length(const struct Queue *q){
    return q->length;
};

struct Queue *queue_init(size_t elem_size, size_t capacity){
    struct Queue *q = malloc(sizeof(struct Queue));
    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->elem_size = elem_size;
    q->data = malloc(elem_size * capacity);

    return q;
};

void queue_dispose(struct Queue *q){
    free(q->data);
    free(q);
};

void queue_enqueue(struct Queue *q, const void *src){
    if(q->length >= q->capacity){
        enlarge_queue_capacity(q);
    }
    void *dest = (char*)q->data + ((q->front + q->length) % q->capacity)*q->elem_size;
    memcpy(dest, src, q->elem_size);
    q->length = q->length + 1;                 /*or ++ or +=*/
};

void queue_dequeue(struct Queue *q, void *dest){
    if(is_empty(q)){return;}
    const void *src = (char*)q->data + (q->front)*q->elem_size;
    memcpy(dest, src, q->elem_size);
    q->front = (q->front + 1) % q->capacity;
    q->length = q->length-1;
};

