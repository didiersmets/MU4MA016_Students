#include <stdbool.h>
#include <stddef.h> // for size_t
#include <string.h>
#include <stdlib.h>


 template <typename T>
 struct Queue {
 size_t front; // index of the first element in the queue
 size_t length; // number of items presently in the queue
 size_t capacity; // capacity of the queue (in nbr of items)
 T *data; // address of the array
 };

template <typename T> bool is_empty(const struct Queue<T> *q);

template <typename T> size_t queue_length(const struct Queue<T> *q);

template <typename T> Queue<T> *queue_init(size_t capacity);

template <typename T> void queue_dispose(struct Queue<T> *q);

template <typename T> void queue_enqueue(struct Queue<T> *q, const T *src);

template <typename T> void queue_dequeue(struct Queue<T> *q, T *dest);

template <typename T> bool is_empty(const struct Queue<T> *q){
    if(q->length == 0){
        return true;
    }
    return false;
}

template <typename T> size_t queue_length(const struct Queue<T> *q){
    return q->length;
}

template <typename T> struct Queue<T> *queue_init(size_t capacity){
    struct Queue<T> *q = (Queue<T>*) malloc(sizeof(struct Queue<T>));
    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->data = new T[capacity];
    return q;
}

template <typename T> void queue_dispose(struct Queue<T> *q){
    free(q->data);
    free(q);
}

template <typename T> static void enlarge_queue_capacity (struct Queue<T> *q){
    T* temp = new T[2*q->capacity];
    for (size_t i=0; i< q->length; i++) {
        temp[i] = q->data[(q->front + i) % q->capacity];
    }
    free(q->data);
    q->data = temp;
    q->front = 0;
    q->capacity = 2 * q->capacity;
    free(temp);
}

template <typename T> void queue_enqueue(struct Queue<T> *q, const T *src){
    if(q->length == q->capacity){
        enlarge_queue_capacity(q);
    }
    //T temp = *src;
    q->data[(q->front + q->length) % q->capacity] = *src;
    q->length = q->length + 1;
}

template <typename T> void queue_dequeue(struct Queue<T> *q, T *dest){
    if(q->length > 0){
        *dest = (q->data[q->front % q->capacity]); // technically % q->capacity is not needed here
        q->length = q->length - 1;
        q->front = (q->front + 1)%q->capacity;
    }
}