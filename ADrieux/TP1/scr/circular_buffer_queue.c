#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "include/circular_buffer_queue.h"

bool is_empty(const struct Queue *q)
{
	assert(q != NULL);
	return(q->length==0);
}

size_t queue_length(const struct Queue *q)
{
	assert(q!=NULL);
	return(q->length);
}

struct Queue *queue_init(size_t elem_size, size_t capacity)
{
	struct Queue *q = malloc(sizeof(struct Queue));
	q->front = 0;
	q->length = 0;
	q->elem_size = elem_size;
	q->data = malloc(elem_size*capacity);
	q->capacity = q->data ? capacity : 0;
	return(q);
}

void queue_dispose(struct Queue *q)
{
	if (q == NULL) {
		return;
	}
	free(q->data);
	free(q);
}

static void enlarge_queue_capacity(struct Queue *q)
{
	assert(q!=NULL);
	if (q->length >= q->capacity)
	{
		size_t new_cap = q->capacity == 0 ? 1 : 2*q->capacity;
		void *new_data = realloc(q->data, new_cap*elem_size);
		void *dest = (char *)q->data + (q->capacity * q->elem_size);
		void *src = q->data;
		memcpy(dest, src, q->elem_size * ();

	}
}

void queue_enqueue(struct Queue *q, const void *src)
{

}

void queue_dequeue(struct Queue *q, void *dest)
{
	assert(q != NULL && q->length >0);
	void *src = (char *)q -> data + (q->front * q->elem_size);
	memcpy(dest, src, q->elem_size);
	q-> front = (front + 1)%q->capacity;
	q->length = length - 1;
	return(q);
}


