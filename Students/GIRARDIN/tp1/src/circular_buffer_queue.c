#include "../include/circular_buffer_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Queue *queue_init(size_t elem_size, size_t capacity){

    struct Queue *q = malloc(sizeof(struct Queue));

    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->elem_size = elem_size;
    q->data = malloc(capacity*elem_size);

    return q;
}

//-------------------------------------------------------------------------------
static void enlarge_queue_capacity(struct Queue *q){

    size_t new_capacity = q->capacity * 2;
    void *tmp = malloc(q->elem_size*new_capacity);

    for(int i = 0; i < q->length; i++){
        void *dest = (char *)tmp + (i * q->elem_size);
        void *src = (char *)q->data + ((q->front + i)%q->capacity)*q->elem_size;
        memcpy(dest, src, q->elem_size); 
    }
    free(q->data);
    q->data = tmp;
    q->capacity = new_capacity;
    q->front = 0;
}

//-------------------------------------------------------------------------------
void queue_enqueue(struct Queue *q, const void *src){

    if(q->length == q->capacity){
        enlarge_queue_capacity(q);
    }

    memcpy((char *)q->data +(q->front + q->length)%q->capacity, src, q->elem_size);
    q->length++;
    q->front = (q->front + q->length)%q->capacity;

}

//-------------------------------------------------------------------------------
void queue_dequeue(struct Queue *q, void *dest){
    if(q->length != 0){
        memcpy(dest, (char *)q->data + (q->front * q->elem_size), q->elem_size);
        q->front = (q->front + 1) % q->capacity;
        q->length--;
    }else{
        printf("Cannot dequeue; the queue is empty !\n");
    }
}