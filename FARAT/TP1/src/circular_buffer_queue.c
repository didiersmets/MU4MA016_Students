#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include "/home/chloe/016/MU4MA016_Students/FARAT/TP1/include/circular_buffer_queue.h"


//struct Queue {
//	size_t front; // index of the first element in the queue
//	size_t length; // number of items presently in the queue
//	size_t capacity; // capacity of the queue (in nbr of items)
//	size_t elem_size; // length in bytes of each item in the queue
//	void *data; // address of the array
//};"


bool is_empty(const struct Queue *q){
	if (q == NULL) {
		return false;}
	else {
		return (q->length == 0);
	}
};

size_t queue_length(const struct Queue *q){
	assert (q != NULL);

	return q->length;
};

struct Queue *queue_init(size_t elem_size, size_t capacity){
	struct Queue *q = malloc(sizeof(elem_size * capacity) + sizeof(elem_size) + 3*sizeof(int));
	q->front = 0;
	q->length = 0;
	q->elem_size = elem_size;
	q->capacity = capacity;
	q->data = malloc(sizeof(elem_size * capacity));
	return q;
};

void queue_dispose(struct Queue *q){
	if (q == NULL){
		return;
	}
	q->length = 0;
	return;
}


static void enlarge_queue_capacity(struct Queue *q);

void queue_enqueue(struct Queue *q, const void *src){
	if (q->length >= q->capacity){
		enlarge_queue_capacity(q);
	}
	size_t tail = (q->front + q->length)% q->capacity;
	void *dest = (char *)(q->data) + tail*(q->elem_size);
	memcpy(dest,src,q->elem_size);
	q->length += 1; 
	return; //pas obligé de mettre ça;
}


void queue_dequeue(struct Queue *q, void *dest){
	void *src = (char *)(q->data) + (q->front)*(q->elem_size);
	memcpy(dest,src,q->elem_size);
	q->length --;
	q->front ++;
}


static void enlarge_queue_capacity(struct Queue *q){
	if (!(q==NULL)){
		q->capacity = 2*q->capacity;
		free(q->data);
		q->data = malloc(sizeof(q->elem_size * q->capacity));
	}
};