#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"circular_buffer_queue.h"
#include <stdbool.h>


static void enlarge_queue_capacity ( struct Queue *q){//RESTRUCTURE!!!!
    if (!q->capacity){
        q->capacity=1;
    }
    int og_capacity=q->capacity;
    q->data=(void *)realloc(q->data, q->capacity*2);
    q->capacity*=2;
    memcpy((char*)q->data+q->elem_size*og_capacity, (char*)q->data, q->elem_size*((q->front-1)%og_capacity));
};

bool is_empty(const struct Queue *q){// the function returns bool 'true' is the queue is indeed empty
    if(q->length ==0){
        return true;
    }
    return false;
};

size_t queue_length(const struct Queue *q){
    return q->length;
};

int queue_init(struct Queue *q, size_t elem_size, size_t capacity){
    if (!is_empty(q)){return-1;}//-1 is the error code
    q->capacity=capacity;
    q->elem_size= elem_size;
    q->data=malloc(elem_size*capacity);
    if (q->data==NULL){return -1;}//-1 is the error code
    q->length=0;
    q->front=0;
    return 0;//0 is success.
};

void queue_dispose(struct Queue *q){
    if(!q){return;}
    else{
        free(q->data);
        free(q);
    }
};

void queue_enqueue(struct Queue *q, const void *src){
    if(q->length==q->capacity){
        enlarge_queue_capacity(q);
    }
    void * dest= q->data+q->elem_size*((q->front+q->length)%q->capacity);
    memcpy((char*)dest, (char*)src, q->elem_size);
    q->length++;
};

void  queue_dequeue(struct Queue *q, void *dest){
    if(is_empty(q)){return ;}
    memcpy((char*)dest, (char*)q->data+q->front*q->elem_size, q->elem_size);
    q->front=(q->front+1)%q->capacity;

};
