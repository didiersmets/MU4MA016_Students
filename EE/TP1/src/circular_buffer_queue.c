#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

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
	struct Queue* q= malloc(sizeof(struct Queue*));
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
	if (is_empty(q)){
		return;
	}
	free(q->data);
	free(q);
}

void queue_enqueue(struct Queue *q, const void *src)
{
	if (q->length < q->capacity){}

void queue_dequeue(struct Queue *q, void *dest)
{
	q->length-=1;
	q->front++;
	return;
}

