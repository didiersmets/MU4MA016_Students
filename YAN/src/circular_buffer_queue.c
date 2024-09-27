#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "circular_buffer_queue.h"

bool is_empty(const struct Queue *q){
	if(){
		return True;
	}
	return False;
}

size_t queue_length(const struct Queue *q){
	return q.length;
}

int queue_init(struct Queue *q, size_t elem_size,size_t capacity){
	q.elem_size = elem_size;
	q.capacity = capacity;
	q.front = 0;
	q.lenght = 0;
	q.data = malloc(elem_size*capacity);
	return 0;
}
void queue_dispose(struct Queue *q){

}

void queue_enqueue(struct Queue *q,const void *src){
	if( q.capacity==q.length){
		enlarge_queue_capacity(q);
		}
	memcpy(q.data[(q.front+q.length)%q.capacity],src,q.elem_size);
	q.length ++;
}

void queue_dequeue(struct Queue *q, void*dest){
	memcpy(dest,q.data[q.front],q.elem_size);
	free(q.data[q.front]);
	q.front = (q.front+1)%q.capacity;
	q.lenght--;
}

static void enlarge_queue_capacity(struct Queue *q){


}






