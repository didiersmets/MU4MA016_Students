#include "circular_buffer_queue.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static void enlarge_queue_capacity(struct Queue *);

bool is_empty(const struct Queue *q) { return (q->length) == 0; }

size_t queue_length(const struct Queue *q) { return q->length; }

template <typename T>
struct Queue *queue_init(size_t capacity) {
	struct Queue *q = malloc(sizeof(struct Queue));
	q->data = (T *)malloc(capacity * sizeof(T));
	q->front = 0;
	q->length = 0;
	q->capacity = capacity;
	return q;
}

void queue_dispose(struct Queue *q) {
	free(q->data);
	free(q);
}

// Push the src to the back of the tail
template <typename T>
void queue_enqueue(struct Queue *q, T val) {
	if (q->length >= q->capacity) {
		size_t old_capacity = q->capacity;
		enlarge_queue_capacity(q);
		// Copy elements before head to after head since capacity was
		// added.
		for (int i = 0; i < q->front; i++) {
			q->data[old_capacity + i] = q->data[i];
		}
	}
	// Enqueue the element.
	size_t tail = (q->front + q->length) % q->capacity;
	q->data[tail] = val;
	q->length++;
	return;
}

// Pull the head element to dest
template <typename T>
queue_dequeue(struct Queue *q) {
	if (is_empty(q)) {
		return NULL
	} else {
		T return_val = q->data[q->front];
		q->front = (q->front + 1) % q->capacity;
		q->length--;
		return T return_val;
	}
}

static void enlarge_queue_capacity(struct Queue *q) {
	q->data = realloc(q->data, ((q->capacity) * 2) * (q->elem_size));
	q->capacity = q->capacity * 2;
}

