#ifndef CIRCULAR_BUFFER_QUEUE_H
#define CIRCULAR_BUFFER_QUEUE_H
#include <stdbool.h>
#include <stddef.h>  // for size_t

struct Queue {
	size_t front;	   // index of the first element in the queue
	size_t length;	   // number of items presently in the queue
	size_t capacity;   // capacity of the queue (in nbr of items)
	size_t elem_size;  // length in bytes of each item in the queue
	void *data;	   // address of the array
};

bool is_empty(const struct Queue *q);

size_t queue_length(const struct Queue *q);

int queue_init(struct Queue *q, size_t elem_size, size_t capacity);

void queue_dispose(struct Queue *q);

void queue_enqueue(struct Queue *q, const void *src);

void queue_dequeue(struct Queue *q, void *dest);

static void enlarge_queue_capacity(struct Queue *q);

#endif