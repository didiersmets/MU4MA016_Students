#include <stdio.h>
#include <stddef.h>                // for size_t
#include "circular_buffer_queue.h" 
#include <stdlib.h>                // needed for malloc
#include <string.h>  // for memcpy
#include <stdbool.h>  // Add this for the bool type

struct Queue *queue_init(size_t elem_size, size_t capacity)
{

    struct Queue *q = malloc(sizeof(struct Queue));
    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->elem_size = elem_size;

    q->data = malloc(elem_size * capacity);

    return q;
}

static void enlarge_queue_capacity(struct Queue *q){
    //if new element is about to hit front, we instead double capacity and add the element there
    size_t new_capacity = q->capacity*2;
    void *new_data = malloc(q->elem_size * new_capacity);
    for(int i = 0; i < q->length; i++){
        char* old_buffer_address = (char*)q->data + ((q->front + i)%q->capacity)*q->elem_size;
        char* new_buffer_address = (char*)new_data + i*q->elem_size;
        memcpy(new_buffer_address, old_buffer_address, q->elem_size);
    }
    free(q->data);
    q->data = new_data;
    q->front = 0;
    q->capacity = new_capacity;
    return;
}

void queue_enqueue(struct Queue *q, const void *src)
{
    
    // more generally, we really just need to check if we will hit front. If we dont, add with modulo operatuobs, if we do, increase buffer size (oof)
    // if we have less elements than we can hold
    if (q->length < q->capacity)
    {
        char *dest = (char *)q->data + (((q->front + q->length) % q->capacity) * q->elem_size);
        memcpy(dest, src, q->elem_size);
        q->length++;
    }

    else
    {
        //we increase buffer size then do the same thing:
        enlarge_queue_capacity(q);
        queue_enqueue(q, src);
    }
}



bool is_empty(const struct Queue *q){
    return q->length == 0;
}
size_t queue_length(const struct Queue *q){
    return q->length;
}

void queue_dequeue(struct Queue *q, void *dest){
    // first, if length 0, whoops
    if (is_empty(q)){
        // printf("Empty queue! \n");
        return;
    } //look up how to handle this better
    
    // check syntax for assigning value to memory at dest
    char *beginning = (char *)q->data + q->front * q->elem_size;
    memcpy(dest, beginning, q->elem_size);
    q->front = (q->front + 1) % q->capacity;
    q->length--;
    return;
}

void queue_dispose(struct Queue *q){
    free(q->data);
    free(q);
    return;
}
