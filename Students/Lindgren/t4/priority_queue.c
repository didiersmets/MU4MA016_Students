#include "priority_queue.h"

#include <stdlib.h>

#define PQ_INITIAL_CAPACITY 16

static void pq_ensure_capacity(struct priority_queue *q) {
    if (q->size < q->capacity) return;

    int new_cap = (q->capacity <= 0) ? PQ_INITIAL_CAPACITY : q->capacity * 2;
    struct priority_data *new_heap =
        (struct priority_data *)realloc(q->heap, (size_t)new_cap * sizeof(*q->heap));
    if (!new_heap) abort();

    q->heap = new_heap;
    q->capacity = new_cap;
}

static int parent(int i) { return (i - 1) / 2; }
static int left(int i)   { return 2 * i + 1; }
static int right(int i)  { return 2 * i + 2; }

static void swap(struct priority_queue *q, int pos1, int pos2) {
    struct priority_data tmp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = tmp;

    if (q->pos_in_heap) {
        int id1 = q->heap[pos1].id;
        int id2 = q->heap[pos2].id;
        if (id1 >= 0 && id1 <= q->max_id) q->pos_in_heap[id1] = pos1;
        if (id2 >= 0 && id2 <= q->max_id) q->pos_in_heap[id2] = pos2;
    }
}

static void sift_up(struct priority_queue *q, int pos) {
    while (pos > 0) {
        int p = parent(pos);
        if (q->heap[p].val <= q->heap[pos].val) break;
        swap(q, p, pos);
        pos = p;
    }
}

static void sift_down(struct priority_queue *q, int pos) {
    for (;;) {
        int l = left(pos);
        int r = right(pos);
        int smallest = pos;

        if (l < q->size && q->heap[l].val < q->heap[smallest].val) smallest = l;
        if (r < q->size && q->heap[r].val < q->heap[smallest].val) smallest = r;

        if (smallest == pos) break;
        swap(q, pos, smallest);
        pos = smallest;
    }
}

int priority_queue_init(struct priority_queue *q, int max_id) {
    if (!q || max_id < 0) return -1;

    q->heap = (struct priority_data *)malloc((size_t)PQ_INITIAL_CAPACITY * sizeof(*q->heap));
    if (!q->heap) return -1;

    q->capacity = PQ_INITIAL_CAPACITY;
    q->size = 0;

    q->max_id = max_id;
    q->pos_in_heap = (int *)malloc((size_t)(max_id + 1) * sizeof(*q->pos_in_heap));
    if (!q->pos_in_heap) {
        free(q->heap);
        q->heap = NULL;
        q->capacity = 0;
        return -1;
    }

    for (int i = 0; i <= max_id; ++i) q->pos_in_heap[i] = -1;
    return 0;
}

void priority_queue_destroy(struct priority_queue *q) {
    if (!q) return;
    free(q->heap);
    free(q->pos_in_heap);
    q->heap = NULL;
    q->pos_in_heap = NULL;
    q->capacity = 0;
    q->size = 0;
    q->max_id = -1;
}

int priority_queue_empty(const struct priority_queue *q) {
    return (!q || q->size == 0) ? 1 : 0;
}

void priority_queue_push(struct priority_queue *q, int id, float val) {
    if (!q) return;
    if (id < 0 || id > q->max_id) return;

    int pos = q->pos_in_heap ? q->pos_in_heap[id] : -1;
    if (pos != -1) {
        float old = q->heap[pos].val;
        q->heap[pos].val = val;
        if (val < old) sift_up(q, pos);
        else if (val > old) sift_down(q, pos);
        return;
    }

    pq_ensure_capacity(q);

    int new_pos = q->size;
    q->heap[new_pos].id = id;
    q->heap[new_pos].val = val;
    q->size++;

    if (q->pos_in_heap) q->pos_in_heap[id] = new_pos;
    sift_up(q, new_pos);
}

struct priority_data priority_queue_pop(struct priority_queue *q) {
    struct priority_data none = { .id = -1, .val = 0.0f };
    if (!q || q->size == 0) return none;

    struct priority_data top = q->heap[0];

    if (q->pos_in_heap && top.id >= 0 && top.id <= q->max_id) {
        q->pos_in_heap[top.id] = -1;
    }

    q->size--;
    if (q->size > 0) {
        q->heap[0] = q->heap[q->size];
        if (q->pos_in_heap) {
            int moved_id = q->heap[0].id;
            if (moved_id >= 0 && moved_id <= q->max_id) q->pos_in_heap[moved_id] = 0;
        }
        sift_down(q, 0);
    }

    return top;
}

void priority_queue_update(struct priority_queue *q, int key, float new_val) {
    if (!q || !q->pos_in_heap) return;
    if (key < 0 || key > q->max_id) return;

    int pos = q->pos_in_heap[key];
    if (pos < 0 || pos >= q->size) return;

    float old = q->heap[pos].val;
    q->heap[pos].val = new_val;

    if (new_val < old) sift_up(q, pos);
    else if (new_val > old) sift_down(q, pos);
}
