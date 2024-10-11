#include "circular_buffer_queue.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static void enlarge_queue_capacity(struct Queue *);

bool is_empty(const struct Queue *q) { return (q->length) == 0; }

size_t queue_length(const struct Queue *q) { return q->length; }

struct Queue *queue_init(size_t elem_size, size_t capacity) {
	struct Queue *q = malloc(sizeof(struct Queue));
	q->data = malloc(capacity * elem_size);
	q->front = 0;
	q->length = 0;
	q->elem_size = elem_size;
	q->capacity = capacity;
	return q;
}

void queue_dispose(struct Queue *q) {
	free(q->data);
	free(q);
}

// Push the src to the back of the tail
void queue_enqueue(struct Queue *q, const void *src) {
	if (q->length >= q->capacity) {
		size_t old_capacity = q->capacity;
		enlarge_queue_capacity(q);
		// Copy elements before head to after head since capacity was
		// added.
		for (int i = 0; i < q->front; i++) {
			memcpy((char *)(q->data) +
				   (old_capacity + i) * (q->elem_size),
			       (char *)(q->data) + i * (q->elem_size),
			       q->elem_size);
		}
	}
	// Enqueue the element.
	size_t tail = (q->front + q->length) % q->capacity;
	memcpy((char *)(q->data) + tail * (q->elem_size), src, q->elem_size);
	q->length++;
	return;
}

// Pull the head element to dest
void queue_dequeue(struct Queue *q, void *dest) {
	if (is_empty(q)) {
	} else {
		memcpy(dest, (char *)(q->data) + (q->front) * (q->elem_size),
		       q->elem_size);
		q->front = (q->front + 1) % q->capacity;
		q->length--;
	}
	return;
}

static void enlarge_queue_capacity(struct Queue *q) {
	q->data = realloc(q->data, ((q->capacity) * 2) * (q->elem_size));
	q->capacity = q->capacity * 2;
}

