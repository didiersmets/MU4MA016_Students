#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct Queue {
	size_t front;
	size_t length;
	size_t capacity;
	size_t elem_size;
	void *data;
};

bool is_empty(const struct Queue *q)
{
	return (q->length == 0);
}

size_t queue_length(const struct Queue *q)
{
	return (q->length);
}

struct Queue *queue_init(size_t elem_size, size_t capacity)
{
	struct Queue* q= (struct Queue*)malloc(sizeof(struct Queue));
	q->front = 0;
	q->length = 0;
	q->data = malloc(capacity*elem_size);
	if (q->data != NULL){
		q->capacity = capacity;
	}else{ 
		q->capacity = 0;
	}
	q->elem_size = elem_size;
	return q;
}

void queue_dispose(struct Queue *q)
{
	free(q->data);
	free(q);
}

static void enlarge_queue_capacity(struct Queue *q)
{
	q->capacity*=2;
	q->data = realloc(q->data,q->capacity * q->elem_size);
	void*dest = (char *)q->data+(q->capacity/2) * q->elem_size;
	memcpy(dest,q->data,q->front*q->elem_size);
	return;
}

void queue_enqueue(struct Queue *q, const void *src)
{	
	if(q->length >= q->capacity){
		enlarge_queue_capacity(q);
	}
	size_t tail = (q->front+q->length)%q->capacity;
	void *dest = (char *)q->data+(tail*q->elem_size);
	memcpy (dest, src,q->elem_size);
	q->length++;
}

void queue_dequeue(struct Queue *q, void *dest)
{
	if (is_empty(q))
		return;
	q->length-=1;
	q->front=(q->front+1)%q->capacity;
}
