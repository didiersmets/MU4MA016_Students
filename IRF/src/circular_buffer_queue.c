#include <stdbool.h>
#include <stddef.h> // for size_t

struct Queue {
	size_t front; // index of the first element in the queue
	size_t length; // number of items presently in the queue
	size_t capacity; // capacity of the queue (in nbr of items)
	size_t elem_size; // length in bytes of each item in the queue
	void *data; // address of the array
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
	struct Queue* q = malloc(sizeof(struct Queue));
	q->front = 0;
	q->length = 0;
	q->elem_size = elem_size;
	q->data = malloc(elem_size*capacity);
	if (q-> data != NULL){
		a->capacity = capacity;
	}else{
		q->capacity = 0;
	}
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

static void enlarge_queue_capacity(struct Queue *q);
{
	q->capacity *=2;
	q->data = realloc(q->data, q->capacity * q->elem_size);
	void *dest = (char *)q->data + (q->capacity / 2) * q->elem_size;
	memcpy(dest, q->data, q->front * q->elem_size);
}



void queue_enqueue(struct Queue *q, const void *src)
{
	if (q->length >= q->capacity){
		enlarge_queue_capacity(q)
	}
	size_t tail = (q->front + q->length) % q->capacity;
	void *dest = (char *)q->data + tail * q->elem_size;
	memcpy (dest, src, q->elem_size);
	q->length++;
}

void queue_dequeue(struct Queue *q, void *dest)
{
	if (q->length > 0){
		void *src = (char *)q->data = q->front * q->elem_size;
		memcpy(dest, src, q->elem_size);
		q->front = (q->front + 1) % q->capacity;
		q->length--;
	}
}




