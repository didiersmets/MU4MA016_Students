#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <circular_buffer_queue.h>

static void enlarge_queue_capacity(struct Queue *q);


void enlarge_queue_capacity(struct Queue *q){
	if(q->length  >= q->capacity){
		size_t l = q->elem_size * q->length + 1;
		q->data = (void *) malloc(2*(l * q->elem_size));
	}
  free(q->data);
  q->data = malloc(q->elem_size * q->capacity);
}

void queue_enqueue(struct Queue *q, const void *src){
  if(q->length  >= q->capacity){
    enlarge_queue_capacity(q);
  }
  const void *src = (const char *)q->data + ((q->front + q->length)%q->capacity)*q-> elem_size;
	memcpy(q->data, src, q->elem_size * q->length);
}

void queue_dequeue(struct Queue *q, void *dest){
  const void *src = (const char*)q->data + (q->front * q->elem_size);
  memcpy(dest, src, q->elem_size);
  q->front += 1;
  q->lenght -= 1;
}

struct Queue *queue_init(size_t elem_size, size_t capacity){
    struct Queue *q = malloc(sizeof(struct Queue));
    q->front=0;
    q->lenght=0;
    q->capacity=capacity;
    q->elem_size=elem_size;
    return q;
  }	

