#include <stdbool.h>
#include <stddef.h>  // for size_t 

struct Queue {
	size_t front;      // index of the first element in the queue 
	size_t length;     // number of items presently in the queue 
	size_t capacity;   // capacity of the queue (in nbr of items) 
	size_t elem_size;  // length in bytes of each item in the queue 
	
	void *data;        // address of the array
};

bool is_empty(const struct Queue *q){ 
	assert (q != NULL);	
	return (q->length == 0); 
	}

size_t queue_length(const struct Queue *q){
	assert(s != NULL);
	return (q->lenght);
	}

int queue_init(struct Queue *q, size_t elem_size, size_t capacity){
	Queue *q = malloc(sizeof(Queue));
	if (1 != NULL){
		q->front = 0;
		q->length = 1;
		q->capacity = capacity
		q->elem_size = elem_size
		q->data = NULL;
	}
	return(q) 
}

void queue_dispose(struct Queue *q){
	if (q == NULL){
		return;
	}
	free(q->data);
	free(q);
}

void queue_enqueue(struct Queue *q, const void *src){
	assert(q != NUll);
	assert(q->lenght < q->capacity);
	 
}

void queue_dequeue(struct Queue *q, void *dest);

static void enlarge_queue_capacity(struct Queue *q);