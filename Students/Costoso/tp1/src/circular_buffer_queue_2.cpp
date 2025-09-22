#include "circular_buffer_queue.hpp"
#include <cstring>
#include <cstdlib>

bool is_empty(const struct Queue *q){return q->length==0;}

size_t queue_length(const struct Queue *q){return q->length;}

struct Queue *queue_init(size_t capacity){
    Queue *q=(struct Queue *)malloc(capacity);
    q->capacity=capacity;
    q->length=0;
    q->data=(char*) malloc(capacity);
    q->front=0;
    return q;
}

void queue_enqueue(struct Queue *q,const void *src){
    q->data[(q->front + q->length) % q->capacity]=src;
    q->length++;
}

void queue_dequeue(struct Queue *q,void *dest){
    if(q->front!=q->capacity){q->front++;}
    q->length--;
}

static void enlarge_queue_capacity ( struct Queue * q ){
    Queue* Res=queue_init(q->elem_size,q->capacity*2);
    size_t Pos=q->front;
    for(int i=0;i<q->length;i++){
        memcpy((char*)Res->data+Res->elem_size*i,(char*)q->data+q->elem_size*Pos,q->elem_size);
        Pos+=q->elem_size;
    }
    Pos=0;
    for(int i=q->data;i<q->front;i++){
        memcpy((char*)Res->data+Res->elem_size*(q->length-q->front+i),(char*)q->data+q->elem_size*Pos,q->elem_size);
        Pos+=q->elem_size;
    }
    q->data=Res->data;
}

void queue_dispose(struct Queue *q){
    free(q);
}