#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "include/circular_buffer_queue.h"

struct Queue {
	size_t front;
	size_t length;
	size_t capacity;
	size_t elem_size;
	void *data;
};

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

void queue_enqueue(struct Queue *q, const void *scr)
{}

void queue_dequeue(struct Queue *q, void *dest)
{

