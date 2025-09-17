#include "circular_buffer_queue.hpp"
#include <cstring>
#include <cstdlib>

bool is_empty(const struct Queue *q){return q->length==0;}

size_t queue_length(const struct Queue *q){return q->length;}

struct Queue *queue_init(size_t elem_size, size_t capacity){
    Queue *q=(struct Queue *)malloc(elem_size*capacity);
    q->elem_size=elem_size;
    q->capacity=capacity;
    q->length=0;
    q->data=(char*) malloc(capacity);
    q->front=0;
    return q;
}

void queue_enqueue(struct Queue *q,const void *src){
    void* dest = (char*)q->data+q->elem_size*((q->front + q->length) % q->capacity);
    memcpy(dest,src,q->elem_size);
    q->length++;
}

void queue_dequeue(struct Queue *q,void *dest){
    if(q->front!=q->capacity){q->front++;}
    q->length--;
}

static void enlarge_queue_capacity ( struct Queue * q ){
    Queue* Res=queue_init(q->elem_size,q->capacity*2);
    size_t Pos=0;
    for(int i=0;i<q->length;i++){
        memcpy((char*)Res->data+Res->elem_size*Pos,(char*)q->data+q->elem_size*Pos,q->elem_size);
        Pos+=q->elem_size;
    }
    q->data=Res->data;
}

void queue_dispose(struct Queue *q){
    free(q);
}