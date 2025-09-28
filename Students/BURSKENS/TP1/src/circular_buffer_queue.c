#include <stdbool.h>
#include <stddef.h> // for size_t
#include <circular_buffer_queue.h>
#include <string.h>
#include <stdlib.h>

bool is_empty(const struct Queue *q){
    if(q->length == 0){
        return true;
    }
    return false;
}

size_t queue_length(const struct Queue *q){
    return q->length;
}

struct Queue *queue_init(size_t elem_size, size_t capacity){
    struct Queue *q = malloc(sizeof(struct Queue));
    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->elem_size = elem_size;
    q->data = malloc(capacity * elem_size);
    return q;
}

void queue_dispose(struct Queue *q){
    free(q->data);
    free(q);
}

static void enlarge_queue_capacity (struct Queue *q){
    size_t old_cap = q->capacity;
    q->capacity = q->capacity * 2;
    q->data=realloc(q->data,q->capacity);
    if (q->front + q->length > old_cap) {
        size_t memory = ((q->front + q->length)%old_cap)*(q->elem_size);
        void *src = (char *)q->data;
        void *dest = (char *)q->data + old_cap * q->elem_size;
        memcpy(dest, src, memory);
    }
}

void queue_enqueue(struct Queue *q, const void *src){
    if(q->length == q->capacity){
        enlarge_queue_capacity(q);
    }
    void *dest = (char *)q->data +((q->front + q->length) % (q->capacity)) * (q->elem_size);
    int el_size = q->elem_size;
    memcpy(dest, src, el_size);
    q->length = q->length + 1;
}

void queue_dequeue(struct Queue *q, void *dest){
    if(q->length > 0){
        void *src = (char *)q->data +(q->front%q->capacity) * q->elem_size;
        memcpy(dest, src, q->elem_size);
        q->length = q->length - 1;
        q->front = (q->front + 1)%q->capacity;
    }
}

