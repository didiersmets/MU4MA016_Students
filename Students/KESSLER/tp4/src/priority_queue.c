#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

static void swap(struct priority_queue *q, int pos1, int pos2) {
    struct priority_data temp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = temp;
    /* keep pos_in_heap consistent with heap positions */
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

int priority_queue_init(struct priority_queue *q, int capacity) {
    q->heap = malloc(sizeof(struct priority_data) * capacity);
    if (!q->heap) {
        fprintf(stderr, "malloc failed for heap\n");
        return -1;
    }
    q->pos_in_heap = malloc(sizeof(int) * capacity);
    if (!q->pos_in_heap) {
        fprintf(stderr, "malloc failed for pos_in_heap\n");
        free(q->heap);
        return -1;
    }
    
    for (int i = 0; i < capacity; i++) {
        q->pos_in_heap[i] = -1; // Initialize positions to -1 (not in heap)
    }

    q->size = 0;
    q->capacity = capacity;
    return 0;
}

void priority_queue_push(struct priority_queue *q, int id, float val) {
    // Edge case: heap full
    if (q->size == q->capacity) {
        printf("Error: Priority queue is full.\n");
        return;
    }

    // Insert new data
    struct priority_data new_data;
    new_data.id = id;
    new_data.val = val;
    q->pos_in_heap[id] = q->size;
    q->heap[q->size++] = new_data;

    // Fix heap
    sift_up(q, q->size - 1);
}

struct priority_data priority_queue_pop(struct priority_queue *q) {
    // Edge case: heap empty
    if (q->size == 0) {
        printf("Error: Priority queue is empty.\n");
        struct priority_data empty_data = {-1, -1.0};
        return empty_data;
    }

    // Store data for return
    struct priority_data top_data = q->heap[0];

    // Delete data in case of single element
    if (q->size == 1) {
        q->size = 0;
        q->pos_in_heap[top_data.id] = -1;
        return top_data;
    }

    /* move last element to root */
    q->heap[0] = q->heap[q->size - 1];
    q->pos_in_heap[q->heap[0].id] = 0;
    q->size--;
    q->pos_in_heap[top_data.id] = -1;

    /* Fix heap */
    sift_down(q, 0);

    return top_data;
}

void priority_queue_update(struct priority_queue *q, int key, float new_val) {
    int pos = q->pos_in_heap[key];
    if (pos == -1) {
        printf("Error: Key not found in priority queue.\n");
        return;
    }

    float old_val = q->heap[pos].val;
    q->heap[pos].val = new_val;

    if (new_val > old_val) {
        sift_up(q, pos);
    } else {
        sift_down(q, pos);
    }
}

