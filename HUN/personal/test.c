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



int queue_init(Queue *q, size_t elem_size , size_t capacity );
void queue_enqueue(Queue *q, const void *src);
void queue_dequeue(Queue *q, void *dest );

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int main() {

  int x1 = 10;
  int x2 = 20;

  Queue *q = malloc(sizeof(Queue));
  queue_init(q, sizeof(int), 10);

  queue_enqueue(q, &(int){100});
  queue_enqueue(q, &x2);

  return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int queue_init(Queue *q, size_t elem_size, size_t capacity) {
  q->capacity = capacity;
  q->elem_size = elem_size;
  q->front = 0;
  q->length = 0;
  q->data = malloc(elem_size * capacity);

  return 0;
}

void queue_enqueue(Queue *q, const void *src) {

  if (q->length == q->capacity) {
    fprintf(stderr, "Error: I dun implement resize yet!");
    exit(EXIT_FAILURE);
  }

  size_t pos = q->length * q->elem_size;
  void *dest =  (char*)q->data + pos; 
  memcpy(dest, src, q->elem_size);
  q->length ++ ;

  // For debuging
  printf("%d\n", *(int *)dest);
}

