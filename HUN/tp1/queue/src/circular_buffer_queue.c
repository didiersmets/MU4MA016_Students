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

size_t queue_length(const struct Queue *q);
bool is_empty(const struct Queue *q);
void queue_enqueue(Queue *q, const void *src);
void queue_dequeue(Queue *q, void *dest );
void queue_dispose(struct Queue *q);
static void enlarge_queue_capacity(struct Queue *q);


//////////////////////////////////////////////////
////////////   IMPLEMENTATION   //////////////////
//////////////////////////////////////////////////

Queue *queue_init(size_t elem_size, size_t capacity) {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->front = 0;
  q->length = 0;
  q->elem_size = elem_size;
  q->capacity = capacity;
  q->data = malloc(elem_size * capacity);
  return q;
}

void queue_enqueue(Queue *q, const void *src) {
  if (q->length >= q->capacity) {
    enlarge_queue_capacity(q);
  }

  size_t pos = (q->length+q->front)%q->capacity;
  void *dest =  (char*)q->data + pos*q->elem_size;
  memcpy(dest, src, q->elem_size);

  q->length += 1 ;
}



void queue_dequeue(Queue *q, void *dest) {
  if (q->length > 0) {
    void *src = (char *)q->data + q->front * q->elem_size;
    memcpy(dest, src, q->elem_size);

    q->front = (q->front + 1) % q->capacity;
    q->length--;
  }
}

void enlarge_queue_capacity(struct Queue *q){
  q->data = realloc(q->data, q->elem_size * q->capacity * 2);

  if (q->front + q->length > q->capacity) {
    void *dest = (char*)q->data + q->capacity*q->elem_size;
    void *src  = q->data;
    memcpy(dest, src, q->elem_size * (q->front + q->length - q->capacity) );
  }

  q->capacity *= 2;
}

void queue_dispose(struct Queue *q) {
  free(q->data);
}



bool is_empty(const struct Queue *q) {
  return (q->length == 0);
}
