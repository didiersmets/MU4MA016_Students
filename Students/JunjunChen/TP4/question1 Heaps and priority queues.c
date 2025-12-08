// question 1 Heaps and priority queues
#include <stdlib.h>
#include <stdio.h>

struct priority_data {
    int id;
    float val;
};

struct priority_queue {
    struct priority_data *heap;
    int capacity;
    int size;
};

static void swap(struct priority_queue *q, int pos1, int pos2) {
    struct priority_data temp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = temp;
}

static void sift_up(struct priority_queue *q, int pos) {
    while (pos > 0) {
        int parent = (pos - 1) / 2;  // mod
        if (q->heap[pos].val >= q->heap[parent].val) {
            swap(q, pos, parent);
            pos = parent;
        }
    }
}

static void sift_down(struct priority_queue *q, int pos) {   
    while (1) {  // infinite loop; break when heap property is satisfied
    int left = 2 * pos + 1;
    int right = 2 * pos + 2;
    int smallest = pos;

    if (left < q->size && q->heap[left].val < q->heap[smallest].val)
        smallest = left;
    if (right < q->size && q->heap[right].val < q->heap[smallest].val)
        smallest = right;

    if (smallest == pos)
        break;

    swap(q, pos, smallest);
    pos = smallest;
    }
}

int priority_queue_init(struct priority_queue *q) {
    q->capacity = 10;
    q->size = 0;
    q->heap = malloc(q->capacity *sizeof(struct priority_data));
};

void priority_queue_push(struct priority_queue *q, int id, float val) {
    if (q->size == q->capacity) {
        q->capacity *= 2;
        q->heap = realloc(q->heap, q->capacity *sizeof(struct priority_data));
    }
    q->heap[q->size].id = id;
    q->heap[q->size].val = val;
    sift_up(q, q->size);
    q->size++;
}

struct priority_data priority_queue_pop(struct priority_queue *q) {
    struct priority_data top = q->heap[0];
    q->size--;
    q->heap[0] = q->heap[q->size];
    sift_down(q,0);
    return top;
}

void priority_queue_update(struct priority_queue *q, int key, float new_val, int *pos_in_heap) {
    int pos = pos_in_heap[key];
    float old_val = q->heap[pos].val;
    q->heap[pos].val = new_val;

    if (new_val < old_val)
        sift_up(q, pos);
    else
        sift_down(q, pos);
}