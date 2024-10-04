#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "circular_buffer_queue.h"

static void enlarge_queue_capacity(struct Queue *q);

bool is_empty(const struct Queue *q){
	if(q->length==0){
		return true;
	}
	return false;
}

size_t queue_length(const struct Queue *q){
	return q->length;
}

int queue_init(struct Queue *q, size_t elem_size,size_t capacity){
	q->elem_size = elem_size;
	q->capacity = capacity;
	q->front = 0;
	q->length = 0;
	q->data = malloc(capacity*elem_size);
	return 0;
}
void queue_dispose(struct Queue *q){
	free(q->data);
}

void queue_enqueue(struct Queue *q,const void *src){
	if( q->capacity==q->length){
		enlarge_queue_capacity(q);
		}
	void *loc = (char*)(q->data)+((q->front+q->length)%q->capacity)*q->elem_size;
	memcpy(loc,src,q->elem_size);
	q->length ++;
}

void queue_dequeue(struct Queue *q, void*dest){
	if(! is_empty(q)){
	void *loc = (char*)(q->data)+q->front*q->elem_size;
	memcpy(dest,loc,q->elem_size);
	q->front = (q->front+1)%q->capacity;
	q->length--;}
}

static void enlarge_queue_capacity(struct Queue *q){
	q->data = realloc(q->data,2*q->capacity*q->elem_size);
	q->capacity = 2*q->capacity;


}






