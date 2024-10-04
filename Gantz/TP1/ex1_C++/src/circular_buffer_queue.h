#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>  // for size_t

template <typename T>
struct Queue {
	size_t front;	   // index of the first element in the queue
	size_t length;	   // number of items presently in the queue
	size_t capacity;   // capacity of the queue (in nbr of items)
	T *data;	   // address of the array
};

template <typename T>
bool is_empty(const struct Queue<T> *q){
	return (q->length == 0);
}

template <typename T>
size_t queue_length(const struct Queue<T> *q){
	return q->length;
}

template <typename T>
struct Queue<T>* queue_init(size_t capacity){
	struct Queue<T>* q = (struct Queue<T>*) malloc(sizeof(struct Queue<T>));
	q->front = 0;
	q->length = 0;
	q->capacity = capacity;
	q->data = (T*) malloc(sizeof(T)*q->capacity);
	return q;
}

template <typename T>
void queue_dispose(struct Queue<T>* q){
	free(q->data);
	free(q);
}

template <typename T>
void queue_enqueue(struct Queue<T>* q, T src){ 
	q->length += 1;

	if(q->length>q->capacity){
		q->capacity *= 2;
		T* data_new = (T*) malloc(sizeof(T)*q->capacity);
		memcpy(data_new,q->data,sizeof(T)*q->capacity);
		free(q->data);
		q->data = data_new;
	}
	q->data[(q->front+q->length)%q->capacity] = src;
}
	
template <typename T>
void queue_dequeue(struct Queue<T>* q, T& dest){
	if(q->length > 0){
		dest = q->data[q->front];
		q->front = (q->front+1)%q->capacity;
		q->length -= 1;
	}
}























