#include <stdlib.h>
#include "priority_queue.h"

int priority_queue_init(struct priority_queue *q, int max_id) {
    q->size = 0;
    q->heap = malloc((max_id + 1) * sizeof(struct priority_data));
    if(q->heap == NULL) {
        return -1; // Memory allocation failed
    }
    q->pos_in_heap = malloc((max_id + 1) * sizeof(int));
    if (q->pos_in_heap == NULL) {
        free(q->heap);
        return -1; // Memory allocation failed
    }
    for (int i = 0; i <= max_id; i++) {
        q->pos_in_heap[i] = -1; // Initialize positions to -1 (not in heap)
    }
    return 0; // Success
}

void priority_queue_free(struct priority_queue *q) {
    free(q->heap);
    q->heap = NULL;
    free(q->pos_in_heap);
    q->pos_in_heap = NULL;
    q->size = 0;
}

static void swap(struct priority_queue *q, int pos1 , int pos2) {
    struct priority_data temp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = temp;
    q->pos_in_heap[q->heap[pos1].id] = pos1;
    q->pos_in_heap[q->heap[pos2].id] = pos2;
}

static void sift_up(struct priority_queue *q, int pos) {
    while (pos > 0) {
        int parent = (pos - 1) / 2;
        if (q->heap[pos].val <= q->heap[parent].val) {
            break;
        }
        swap(q, pos, parent);
        pos = parent;
    }
}

static void sift_down(struct priority_queue *q, int pos) {
    while (1) {
        int left = 2 * pos + 1;
        int right = 2 * pos + 2;
        int largest = pos;

        if (left < q->size && q->heap[left].val > q->heap[largest].val) {
            largest = left;
        }
        if (right < q->size && q->heap[right].val > q->heap[largest].val) {
            largest = right;
        }
        if (largest == pos) {
            break;
        }
        swap(q, pos, largest);
        pos = largest;
    }
}

void priority_queue_push(struct priority_queue *q, int id, float val) {
    q->heap[q->size].id = id;
    q->heap[q->size].val = val;
    q->pos_in_heap[id] = q->size;
    sift_up(q, q->size);
    q->size++;
}

struct priority_data priority_queue_pop(struct priority_queue *q) {
    struct priority_data top = q->heap[0];
    q->heap[0] = q->heap[q->size - 1];
    q->pos_in_heap[q->heap[0].id] = 0;
    q->size--;
    sift_down(q, 0);
    return top;
}

void priority_queue_update(struct priority_queue *q, int key , float new_val) {
    int pos = q->pos_in_heap[key];
    if (pos == -1) {
        // Key not found in the priority queue
        priority_queue_push(q, key, new_val);
        return;
    }
    float old_val = q->heap[pos].val;
    q->heap[pos].val = new_val;
    if (new_val > old_val) {
        sift_up(q, pos);
    } else if (new_val < old_val) {
        sift_down(q, pos);
    }
}