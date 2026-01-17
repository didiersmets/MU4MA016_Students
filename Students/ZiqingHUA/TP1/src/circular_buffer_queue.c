#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "/users/home/28624202/MU4MA016_Students/ADrieux/TP1/include/circular_buffer_queue.h"

bool is_empty(const struct Queue *q)
{
	assert(q != NULL);
	return (q->length==0);
}

size_t queue_length(const struct Queue *q)
{
	assert(q!=NULL);
	return(q->length);
}

struct Queue *queue_init(size_t elem_size, size_t capacity)
{
	struct Queue *q =(struct Queue *)malloc(sizeof(struct Queue));
	q->front = 0;
	q->length = 0;
	q->elem_size = elem_size;
	q->capacity = capacity;
	q->data =(void *)malloc(elem_size*capacity);
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
	size_t old_capacity = q->capacity;
	size_t new_capacity = old_capacity == 0 ? 1 : 2*old_capacity;
	q->data = realloc(q->data, new_capacity*q->elem_size);
	q->capacity = new_capacity;
	for (int i = 0; i < q->front; i++)
	{
		void *dest = (char *)q->data + (old_capacity + i)*q->elem_size;
		void *src = (char *)q->data + i*q->elem_size;
		memcpy(dest, src, q->elem_size);
	}
}


void queue_enqueue(struct Queue *q, const void *src)
{
	if (queue_length(q) >= q->capacity)
	{
		enlarge_queue_capacity(q);
	}
	size_t tail = (q->front + q->length)%q->capacity;
	void *dest = (char *)q->data + tail*q->elem_size;
	memcpy(dest, src, q->elem_size);
	q->length = q->length + 1;
}

void queue_dequeue(struct Queue *q, void *dest)
{
	assert(q != NULL);
	if (queue_length(q) > 0) {
		void *src = (char *)q->data + (q->front*q->elem_size);
	        memcpy(dest, src, q->elem_size);
	        q-> front = (q->front + 1)%q->capacity;
	        q->length = q-> length - 1;
	}
}


