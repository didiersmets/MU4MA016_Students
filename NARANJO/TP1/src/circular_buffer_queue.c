#include <stdbool.h>
#include <stddef.h>  // for size_t 
#include <string.h>
#include <assert.h>
#include <stdlib.h>



struct Queue {
	size_t front;      // index of the first element in the queue 
	size_t length;     // number of items presently in the queue 
	size_t capacity;   // capacity of the queue (in nbr of items) 
	size_t elem_size;  // length in bytes of each item in the queue 
	
	void *data;        // address of the array
};

bool is_empty(const struct Queue *q)
{ 
	assert (q != NULL);	
	return (q->length == 0); 
}

size_t queue_length(const struct Queue *q)
{
	assert(q != NULL);
	return (q->length);
}


static void enlarge_queue_capacity(struct Queue *q)
{
        q->capacity *= 2;

}


struct Queue* queue_init(size_t elem_size, size_t capacity)
{
	struct Queue *q = malloc(sizeof(struct Queue));
	if (q != NULL){
		q->front = 0;
		q->length = 0;
		q->capacity = capacity;
		q->elem_size = elem_size;
		q->data = malloc(capacity*elem_size);
	}
	return(q); 
}

void queue_dispose(struct Queue *q)
{
	if (q == NULL){
		return;
	}
	free(q->data);
	free(q);
}

void queue_enqueue(struct Queue *q, const void *src)
{
	assert(q != NULL);

	if (q->length >= q->capacity){
		enlarge_queue_capacity(q);
		void* data_new = malloc(q->capacity*q->elem_size);
		memcpy(data_new, q->data, q->elem_size*q->capacity);
		free(q->data);
		q->data = data_new;
	}
	q->length += 1;
	size_t tail = (q->front + q->length)%q->capacity;
	memcpy((char*)q->data + tail*(q->elem_size), src, 1);	 
}

void queue_dequeue(struct Queue *q, void *dest)
{
	assert(q != NULL);
	if (q->length > 0){
		memcpy(dest, (char*)q->data + q->front * q->elem_size, 1);
		q->front = (q->front + 1)%q->capacity;
		q->length -= 1;
	}
}






