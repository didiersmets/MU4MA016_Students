/* include/circular_buffer_queue.h */
#ifndef CIRCULAR_BUFFER_QUEUE_H
#define CIRCULAR_BUFFER_QUEUE_H

#include <stddef.h>  // for size_t 

// Public queue structure 
struct Queue {
    size_t front;      // index of the first element in the queue 
    size_t length;     // current number of elements in the queue 
    size_t capacity;   // capacity of the queue 
    size_t elem_size;  // size in bytes of one element 
    void  *data;       // pointer to the underlying array 
};

/* Create a new queue capable of holding 'capacity' elements of size 'elem_size'. */
struct Queue *queue_init(size_t elem_size, size_t capacity);

/* Enqueue one element pointed to by 'src'. */
void queue_enqueue(struct Queue *q, const void *src);

/* Dequeue one element and copy it into 'dest'. */
void queue_dequeue(struct Queue *q, void *dest);

/* Free the internal array and the queue structure itself. */
void queue_dispose(struct Queue *q);

#endif /* CIRCULAR_BUFFER_QUEUE_H */


