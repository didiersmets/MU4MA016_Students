#include <stdio.h>
#include <stdbool.h>
#include <stddef.h> // for size_t
#include <string.h>
#include <assert.h>
#include <stdlib.h>

struct Queue
{
  size_t front; // index of the first element in the queue
  size_t length; // number of items presently in the queue
  size_t capacity; // capacity of the queue (in nbr of items)
  size_t elem_size; // length in bytes of each item in the queue
  void *data; // address of the array
};

bool is_empty(const struct Queue *q)
{
  assert (q != NULL);
  return (q -> length == 0);
};

size_t queue_length(const struct Queue *q)
{
  assert (q != NULL);
  return (q->length);
};

struct Queue *queue_init(size_t elem_size, size_t capacity)
{
  struct Queue *q = malloc(sizeof(struct Queue));
  if (q != NULL){
    q -> front = 0;
    q -> length = 0;
    q -> capacity = capacity;
    q -> elem_size = elem_size;
    q -> data = malloc(capacity * elem_size);
  }
  return (q);
};

void queue_dispose(struct Queue *q)
{
  if(q == NULL){
    return;
  }
  free(q -> data);
  free(q);
};

void queue_enqueue(struct Queue *q, const void *src)
{
  while (q -> length >= q -> capacity){
    enlarge_queue_capacity(q);
  }
  void * place = (char*)(q->data) + ((q -> front + q -> length)%(q->capacity)) * q->elem_size;
  memcpy(place,src,q -> elem_size);
  q->length += 1;
};

void queue_dequeue(struct Queue *q, void *dest)
{
  void * src = (char*)(q->data) + ((q -> front + q -> length)%q->capacity ) * q->elem_size;
  memcpy(dest , src , q -> elem_size);
  q->length -= 1;
};

static void enlarge_queue_capacity ( struct Queue * q )
{
  size_t double_cap = 2 * q -> capacity;
  q -> capacity = double_cap;
};
