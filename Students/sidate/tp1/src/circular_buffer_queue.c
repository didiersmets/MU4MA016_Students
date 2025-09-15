#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <circular_buffer_queue.h>

static void enlarge_queue_capacity(struct Queue *q);


void enlarge_queue_capacity(struct Queue *q){
	if(q.length  >= q.capacity){
		size_t l = q.elem_size * q.length + 1;
		q.data = (void *) malloc(2*(l * q.elem_size));

	}
}

void queue_enqueue(struct Queue *q, const void *src){
	const void *src = (const char *)q->data + ((q->front + q->length)%q->capacity)*q-> elem_size;
	memecpy(q.data, src, q.elem_size * q.length);
}

void queue_dequeue(struct Queue *q, void *dest){

	memcpy(dest, q.data, q.elem_size * q.length);

	



