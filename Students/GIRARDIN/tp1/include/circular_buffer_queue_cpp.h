#include <stdbool.h>
#include <stddef.h> // for size_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <typename T>
struct Queue {
	size_t  front;      // index of the first element in the queue
	size_t  length;     // number of items presently in the queue
	size_t  capacity;   // capacity of the queue (in nbr of items)
	T       *data;      // address of the array
};

template <typename T>
bool is_empty(const Queue<T> *q);

template <typename T>
size_t queue_length(const Queue<T> *q);

template <typename T>
struct Queue<T> *queue_init(size_t capacity);

template <typename T>
void queue_dispose(Queue<T> *q);

template <typename T>
void queue_enqueue(Queue<T> *q, const void *src);

template <typename T>
void queue_dequeue(Queue<T> *q, void *dest);

//===========================================================================================
template <typename T>
bool is_empty(const Queue<T> *q){
    return !(q->length);
}

//---------------------------------------------------------------------------------
template <typename T>
size_t queue_length(const Queue<T> *q){
    return q->length;
}

//---------------------------------------------------------------------------------
template <typename T>
struct Queue<T> *queue_init(size_t capacity){

    struct Queue<T> *q = (Queue<T>*) malloc(sizeof(Queue<T>));

    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->data = new T[capacity];

    return q;
}

//---------------------------------------------------------------------------------
template <typename T>
void queue_dispose(Queue<T> *q){
    free(q->data);
    free(q);
}

//-------------------------------------------------------------------------------
template <typename T>
static void enlarge_queue_capacity(Queue<T> *q){

    size_t new_capacity = q->capacity * 2;
    T *tmp = new T[new_capacity];

    for(int i = 0; i < q->length; i++){
        tmp[i] = q->data[(q->front + i) % q->capacity];
    }
    
    free(q->data);
    q->data = tmp;
    q->capacity = new_capacity;
    q->front = 0;
}

//---------------------------------------------------------------------------------
template <typename T>
void queue_enqueue(Queue<T> *q, const T *src){
    if(q->length == q->capacity){
        enlarge_queue_capacity(q);
    }

    q->data[(q->front + q->length)%q->capacity] = *src;
    q->length++;
    q->front = (q->front + q->length)%q->capacity;
}

//---------------------------------------------------------------------------------
template <typename T>
void queue_dequeue(Queue<T> *q, T *dest){
    if(!is_empty(q)){
        *dest = q->data[q->front];
        q->front = (q->front + 1) % q->capacity;
        q->length--;
    }else{
        printf("Cannot dequeue; the queue is empty !\n");
    }
}