#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct Queue {
  size_t front;		// index of the first element in the queue
  size_t length;	// number of items presently in the queue
  size_t capacity;	// capacity of the queue (in nbr of items)
  size_t elem_size;	// length in bytes of each item in the queue
  void *data;		// address of the array
} Queue;




Queue *queue_init(size_t elem_size , size_t capacity );

size_t queue_length(const struct Queue *q);

bool is_empty(const struct Queue *q);

void queue_enqueue(Queue *q, const void *src);

void queue_dequeue(Queue *q, void *dest );

void queue_dispose(struct Queue *q);
