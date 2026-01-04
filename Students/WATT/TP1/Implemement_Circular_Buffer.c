/* Standard headers */
#include <stdlib.h>   /* malloc, free, realloc, EXIT_FAILURE */
#include <string.h>   /* memcpy */
#include <assert.h>   /* assert */

#include "circular_buffer_queue.h"  /* our own header */

/* 
 * Internal helper: enlarge the capacity of the queue's circular buffer.
 * Not part of the public API -> marked static.
 */
static void enlarge_queue_capacity(struct Queue *q)
{
    /* Sanity check: q should not be NULL. */
    assert(q != NULL);

    /* Choose new capacity: start at 1 if currently 0, else double it. */
    size_t new_capacity = (q->capacity == 0) ? 1 : 2 * q->capacity;

    /* Allocate new buffer with enough room for new_capacity elements. */
    void *new_data = malloc(new_capacity * q->elem_size);

    /* If allocation fails, we can't continue safely. */
    if (new_data == NULL) {
        /* For a small TP we can simply abort; a robust library would handle this more gracefully. */
        exit(EXIT_FAILURE);
    }

    /*
     * If old capacity was 0, there is nothing to copy: queue was empty
     * and data == NULL. Just install the new buffer.
     */
    if (q->capacity == 0) {
        q->data     = new_data; /* remember new array */
        q->capacity = new_capacity; /* update capacity */
        q->front    = 0;        /* front index resets to 0 */
        return;                 /* done */
    }

    /*
     * Copy existing elements from old circular buffer into new_data
     * in the logical order: element 0 of queue goes to index 0, etc.
     */
    char *old_bytes = (char *)q->data;       /* for byte-wise pointer arithmetic */
    char *new_bytes = (char *)new_data;      /* same for new buffer */

    for (size_t i = 0; i < q->length; ++i) {
        /* Compute index in old circular buffer: (front + i) mod old_capacity */
        size_t old_index = q->front + i;
        if (old_index >= q->capacity) {      /* manual mod to avoid % 0 issues */
            old_index -= q->capacity;
        }

        /* Source address of element i in old buffer */
        void *src = old_bytes + old_index * q->elem_size;

        /* Destination address for element i in new buffer (no wrap now) */
        void *dst = new_bytes + i * q->elem_size;

        /* Copy one element */
        memcpy(dst, src, q->elem_size);
    }

    /* Free old data buffer */
    free(q->data);

    /* Install newly allocated buffer and metadata */
    q->data     = new_data;
    q->capacity = new_capacity;

    /*
     * After reallocation and copy, the first element is now at index 0,
     * and the queue occupies indices 0 .. length-1.
     */
    q->front = 0;
}

/*
 * Public function: create and initialize a new queue.
 */
struct Queue *queue_init(size_t elem_size, size_t capacity)
{
    /* Allocate memory for the Queue structure itself. */
    struct Queue *q = malloc(sizeof(struct Queue));

    /* If allocation failed, return NULL so the caller can handle it. */
    if (q == NULL) {
        return NULL;
    }

    /* Initialize queue metadata. */
    q->front     = 0;          /* no elements yet, so front = 0 */
    q->length    = 0;          /* empty queue */
    q->elem_size = elem_size;  /* store size of each element */
    q->capacity  = capacity;   /* initial capacity as requested */

    /* Allocate storage array if capacity > 0, else leave data = NULL. */
    if (capacity > 0) {
        q->data = malloc(capacity * elem_size);
        if (q->data == NULL) {
            /* Allocation failed: clean up and signal failure. */
            free(q);
            return NULL;
        }
    } else {
        q->data = NULL; /* will be allocated later on first enlarge */
    }

    /* Return pointer to newly created queue. */
    return q;
}

/*
 * Public function: enqueue one element to the back of the queue.
 */
void queue_enqueue(struct Queue *q, const void *src)
{
    /* Basic sanity check: queue must exist. */
    assert(q != NULL);

    /*
     * If the queue is full (length == capacity), enlarge the buffer
     * before inserting the new element.
     */
    if (q->length >= q->capacity) {
        enlarge_queue_capacity(q);
    }

    /* Now we are guaranteed that capacity > 0 and length < capacity. */

    /* Compute the index of the new tail element in circular fashion. */
    size_t tail_index = q->front + q->length;
    if (tail_index >= q->capacity) { /* manual mod capacity */
        tail_index -= q->capacity;
    }

    /* Compute destination address for the new element. */
    char *bytes = (char *)q->data;
    void *dst = bytes + tail_index * q->elem_size;

    /* Copy the element bytes from src into our queue storage. */
    memcpy(dst, src, q->elem_size);

    /* We have one more element now. */
    q->length += 1;
}

/*
 * Public function: dequeue one element from the front of the queue.
 */
void queue_dequeue(struct Queue *q, void *dest)
{
    /* Queue must not be NULL and must not be empty. */
    assert(q != NULL);
    assert(q->length > 0);

    /* Address of the front element in the circular buffer. */
    char *bytes = (char *)q->data;
    void *src = bytes + q->front * q->elem_size;

    /*
     * Copy the front element into user-provided storage.
     * (If dest is NULL, you might skip the copy, but the API
     * suggests dest is meant to be valid.)
     */
    if (dest != NULL) {
        memcpy(dest, src, q->elem_size);
    }

    /*
     * Move front one step forward circularly.
     * If we were at the last index, this wraps back to 0.
     */
    q->front += 1;
    if (q->front >= q->capacity) {
        q->front = 0;
    }

    /* One fewer element now. */
    q->length -= 1;

    /*
     * Optional micro-optimization: when queue becomes empty,
     * we can reset front to 0 for tidiness.
     */
    if (q->length == 0) {
        q->front = 0;
    }
}

/*
 * Public function: free all memory associated with the queue.
 */
void queue_dispose(struct Queue *q)
{
    /* If the pointer is NULL, nothing to do. */
    if (q == NULL) {
        return;
    }

    /* Free the internal data buffer (if it exists). */
    free(q->data);

    /* Free the Queue structure itself. */
    free(q);
}
