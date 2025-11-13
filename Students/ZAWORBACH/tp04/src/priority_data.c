// initialize priority queue
#include <stdlib.h>
#include "../include/priority_queue.h"

int priority_queue_init ( struct priority_queue * q ) {
    q->capacity = 10;
    q->size = 0;
    q->heap = (struct priority_data *) malloc (q->capacity * sizeof (struct priority_data));
    if ( q->heap == NULL ) {
        return -1; // memory allocation failed
    }
    return 0; // success
}


void priority_queue_push ( struct priority_queue *q , int id , float val ) {
    if ( q->size >= q->capacity ) {
        // resize heap
        q->capacity *= 2;
        q->heap = (struct priority_data *) realloc (q->heap , q->capacity * sizeof (struct priority_data));
    }
    q->heap[q->size].data = id;
    q->heap[q->size].priority = val;
    sift_up ( q , q->size );
    q->size++;
}

// sift up to maintain heap property
static void sift_up ( struct priority_queue *q , int pos ) {
    while ( pos > 0 ) {
        int parent = ( pos - 1 ) / 2;
        if ( q->heap[pos].priority <= q->heap[parent].priority ) {
            break;
        }
        swap ( q , pos , parent );
        pos = parent;
    }     
}

static void swap ( struct priority_queue *q , int pos1 , int pos2 ) {
    struct priority_data temp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = temp;
}

struct priority_data priority_queue_pop ( struct priority_queue * q ) {
    struct priority_data top = q->heap[0];
    q->heap[0] = q->heap[q->size - 1];
    q->size--;
    sift_down ( q , 0 );
    return top;
}

static void sift_down ( struct priority_queue *q , int pos ) {
    while ( 1 ) {
        int left = 2 * pos + 1;
        int right = 2 * pos + 2;
        int largest = pos;
        if ( left < q->size && q->heap[left].priority > q->heap[largest].priority ) {
            largest = left;
        }
        if ( right < q->size && q->heap[right].priority > q->heap[largest].priority ) {
            largest = right;
        }
        if ( largest == pos ) {
            break;
        }
        swap ( q , pos , largest );
        pos = largest;
    }
}   

