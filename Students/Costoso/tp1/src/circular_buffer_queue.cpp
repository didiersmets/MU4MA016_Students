#include "circular_buffer_queue.hpp"
#include <cstring>

bool is_empty(const struct Queue *q){return q.length==0;}

size_t queue_lenght(const struct Queue *q){return q.length;}

struct Queue *queue_init(size_t elem_size, size_t capacity){
    Queue Res;
    Res.elem_size=elem_size;
    Res.capacity=capacity;
    Res.length=0;
    Res.data=(char*) malloc(capacity);
    Res.front=0;
    return Res;
}

void queue_enqueue(struct Queue *q,const void *src){
    if(q.lenght == q.capacity){
        enlarge_queue_capacity(q);
    }
    void* Pos = (char*)q.data+q.elem_size*q.front;
    for(int i=0;i<q.length;i++){
        if(Pos==(char*)q.data+q.elem_size*q.capacity){
            Pos=(char*)q.data;
        }
        Pos+=elem_size;
    }
    memcpy(Pos,src,elem_size);
    q.lenght++;
}

void queue_dequeue(struct Queue *q,const void *src){
    q.front++;
    if(q.front==q.capacity){
            q.front=0;
        }
}

static void enlarge_queue_capacity ( struct Queue * q ){
    Queue Res=queue_init(q.elem_size,q.capacity*2)
    size_t Pos=0;
    for(int i=0;i<q.length;i++){
        memcpy((char*)Res.data+Res.elem_size*Pos,(char*)q.data+q.elem_size*Pos,elem_size);
        Pos+=elem_size;
    }
    q.data=q.Res;
}