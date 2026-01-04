#pragma once

/* TP4 - Section 1: Heaps and priority queues (with updatable priorities) */

#include <stddef.h>

struct priority_data {
    int id;
    float val;
};

struct priority_queue {
    struct priority_data *heap;
    int capacity;
    int size;
    int *pos_in_heap; /* pos_in_heap[id] = position in heap, or -1 if absent */
};

/* Init with an upper bound on ids (max_id). Allocates pos_in_heap[max_id+1]. */
int priority_queue_init(struct priority_queue *q, int max_id);

/* Free internal buffers (not requested in the statement, but essential in practice). */
void priority_queue_free(struct priority_queue *q);

/* Insert (id,val). If id already exists, this behaves like update(id,val). */
void priority_queue_push(struct priority_queue *q, int id, float val);

/* Remove and return the element with minimal val (min-heap). q must be non-empty. */
struct priority_data priority_queue_pop(struct priority_queue *q);

/* Update the priority value of an existing id (or inserts if absent). */
void priority_queue_update(struct priority_queue *q, int id, float new_val);
