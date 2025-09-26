#include "circular_buffer_queue_2.h"
#include <cstring>
#include <cstdlib>
template <typename T>
bool is_empty(const struct Queue<T> *q){return q->length==0;}

template <typename T>
size_t queue_length(const struct Queue<T> *q){return q->length;}

template <typename T>
struct Queue<T> *queue_init(size_t capacity){
    Queue<T> *q=(struct Queue<T> *)malloc(capacity);
    q->capacity=capacity;
    q->length=0;
    q->data=(char*) malloc(capacity);
    q->front=0;
    return q;
}

template <typename T>
void queue_enqueue(struct Queue<T> *q,const void *src){
    q->data[(q->front + q->length) % q->capacity]=src;
    q->length++;
}

template <typename T>
void queue_dequeue(struct Queue<T> *q,void *dest){
    if(q->front!=q->capacity){q->front++;}
    q->length--;
}

template <typename T>
static void enlarge_queue_capacity ( struct Queue<T> * q ){
    size_t new_cap = q->capacity ? 2 * q->capacity : 1;
    T *next_data = (char*)malloc(new_cap);
    q->capacity=new_cap;
    size_t Pos = 0;
    for (int i = 0; i < q->length; i++) {
        next_data[Pos]=q->data[Pos];
        Pos ++;
    }
    free(q->data);
    q->data=next_data;
}

template <typename T>
void queue_dispose(struct Queue<T> *q){
    free(q);
}