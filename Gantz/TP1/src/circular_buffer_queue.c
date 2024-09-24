#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/circular_buffer_queue.h"

typedef struct Queue Q;

bool is_empty(const Q* q){
	return (q->length == 0);
}

size_t queue_length(const Q* q){
	return q->length;
}

Q* queue_init(size_t elem_size, size_t capacity){
	Q* q = (Q*) malloc(sizeof(Q));
	q->front = 0;
	q->length = 0;
	q->capacity = capacity;
	q->elem_size = elem_size;
	q->data = malloc(capacity*elem_size);
	return q;
}

void queue_dispose(Q* q){
	free(q->data);
	free(q);
}

void queue_enqueue(Q* q, const void* src){ 
	q->length += 1;

	if(q->length>q->capacity){
		q->capacity *= 2;
		void* data_new = malloc(q->capacity*q->elem_size);
		memcpy(data_new,q->data,q->elem_size*q->capacity);
		free(q->data);
		q->data = data_new;
	}
	memcpy((char*)q->data + ((q->front+q->length)%q->capacity)*q->elem_size, src, 1);
}
	
void queue_dequeue(Q* q, void* dest){
	if(q->length > 0){
		memcpy(dest,(char*)q->data+q->front*q->elem_size,1);
		q->front = (q->front+1)%q->capacity;
		q->length -= 1;
	} else {
		printf("empty queue");
	}
}























