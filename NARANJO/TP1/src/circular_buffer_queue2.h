#include <stdbool.h>
#include <stddef.h>  // for size_t 
#include <string.h>
#include <assert.h>
#include <stdlib.h>


template <typename T>
struct Queue {
	size_t front;      // index of the first element in the queue 
	size_t length;     // number of items presently in the queue 
	size_t capacity;   // capacity of the queue (in nbr of items) 
		
	T *data;           // address of the array
};

template <typename T>
bool is_empty(const struct Queue<T> *q)
{ 
	assert (q != NULL);	
	return (q->length == 0); 
}

template <typename T>
size_t queue_length(const struct Queue<T> *q)
{
	assert(q != NULL);
	return (q->length);
}

template <typename T>
static void enlarge_queue_capacity(struct Queue<T> *q)
{
        q->capacity *= 2;
}

template <typename T>
struct Queue<T>* queue_init(size_t capacity)
{
	struct Queue<T>* q = (struct Queue<T>*)malloc(sizeof(struct Queue<T>));
	if (q != NULL){
		q->front = 0;
		q->length = 0;
		q->capacity = capacity;
		q->data = malloc(capacity*sizeof(T));
	}
	return(q); 
}

template <typename T>
void queue_dispose(struct Queue<T> *q)
{
	if (q == NULL){
		return;
	}
	free(q->data);
	free(q);
}

template <typename T>
void queue_enqueue(struct Queue<T> *q, const void *src)
{
	assert(q != NULL);

	if (q->length >= q->capacity){
		enlarge_queue_capacity(q);
		void* data_new = malloc(q->capacity*sizeof(T));
		data_new = q->data[sizeof(T)*q->capacity];
		free(q->data);
		q->data = data_new;
	}
	q->length += 1;
	size_t tail = (q->front + q->length)%q->capacity;
	memcpy((char*)q->data + tail*(sizeof(T)), src, 1);	 
}

template <typename T>
void queue_dequeue(struct Queue<T> *q)
{
	assert(q != NULL);
	if (q->length > 0){
		T dest = q->data[q->front];
		q->front = (q->front + 1)%q->capacity;
		q->length -= 1;
	}
}




