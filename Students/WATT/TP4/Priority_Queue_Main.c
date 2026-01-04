#include "Priority_Queue.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/* ---------- Internal helpers (not part of the public API) ---------- */

/* Return 1 if a should be above b in the heap (min-heap by val, tie-break by id). */
static int higher_priority(const struct priority_data *a,
                           const struct priority_data *b)
{
    if (a->val < b->val) return 1;
    if (a->val > b->val) return 0;
    return (a->id < b->id);
}

static void swap(struct priority_queue *q, int pos1, int pos2)
{
    struct priority_data tmp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = tmp;

    if (q->pos_in_heap) {
        q->pos_in_heap[q->heap[pos1].id] = pos1;
        q->pos_in_heap[q->heap[pos2].id] = pos2;
    }
}

static void sift_up(struct priority_queue *q, int pos)
{
    while (pos > 0) {
        int parent = (pos - 1) / 2;
        if (higher_priority(&q->heap[pos], &q->heap[parent])) {
            swap(q, pos, parent);
            pos = parent;
        } else {
            break;
        }
    }
}

static void sift_down(struct priority_queue *q, int pos)
{
    for (;;) {
        int left = 2 * pos + 1;
        int right = 2 * pos + 2;
        int best = pos;

        if (left < q->size && higher_priority(&q->heap[left], &q->heap[best])) {
            best = left;
        }
        if (right < q->size && higher_priority(&q->heap[right], &q->heap[best])) {
            best = right;
        }

        if (best != pos) {
            swap(q, pos, best);
            pos = best;
        } else {
            break;
        }
    }
}

static void ensure_capacity(struct priority_queue *q, int needed)
{
    if (q->capacity >= needed) return;

    int new_cap = (q->capacity <= 0) ? 8 : q->capacity;
    while (new_cap < needed) new_cap *= 2;

    struct priority_data *new_heap =
        (struct priority_data *)realloc(q->heap, (size_t)new_cap * sizeof(*q->heap));
    if (!new_heap) {
        /* In coursework contexts, aborting on OOM is acceptable and makes bugs obvious. */
        abort();
    }
    q->heap = new_heap;
    q->capacity = new_cap;
}

/* ------------------------- Public API ------------------------- */

int priority_queue_init(struct priority_queue *q, int max_id)
{
    if (!q || max_id < 0) return -1;

    q->heap = NULL;
    q->capacity = 0;
    q->size = 0;

    q->pos_in_heap = (int *)malloc((size_t)(max_id + 1) * sizeof(int));
    if (!q->pos_in_heap) {
        return -1;
    }
    for (int i = 0; i <= max_id; i++) {
        q->pos_in_heap[i] = -1;
    }
    return 0;
}

void priority_queue_free(struct priority_queue *q)
{
    if (!q) return;
    free(q->heap);
    free(q->pos_in_heap);
    q->heap = NULL;
    q->pos_in_heap = NULL;
    q->capacity = 0;
    q->size = 0;
}

void priority_queue_push(struct priority_queue *q, int id, float val)
{
    assert(q != NULL);
    assert(q->pos_in_heap != NULL);
    assert(id >= 0);

    /* ids are unique; if already present, treat as update */
    int pos = q->pos_in_heap[id];
    if (pos != -1) {
        /* already present: update */
        /* (this is a safe behavior and matches typical Dijkstra usage) */
        /* You can change this to assert(pos == -1) if you want strict inserts. */
        float old = q->heap[pos].val;
        q->heap[pos].val = val;
        if (val < old) sift_up(q, pos);
        else if (val > old) sift_down(q, pos);
        return;
    }

    ensure_capacity(q, q->size + 1);

    int new_pos = q->size;
    q->heap[new_pos].id = id;
    q->heap[new_pos].val = val;
    q->size++;

    q->pos_in_heap[id] = new_pos;
    sift_up(q, new_pos);
}

struct priority_data priority_queue_pop(struct priority_queue *q)
{
    assert(q != NULL);
    assert(q->pos_in_heap != NULL);
    assert(q->size > 0);

    struct priority_data top = q->heap[0];

    /* Mark removed */
    q->pos_in_heap[top.id] = -1;

    q->size--;
    if (q->size == 0) {
        return top;
    }

    /* Move last to root */
    q->heap[0] = q->heap[q->size];
    q->pos_in_heap[q->heap[0].id] = 0;

    sift_down(q, 0);
    return top;
}

void priority_queue_update(struct priority_queue *q, int id, float new_val)
{
    assert(q != NULL);
    assert(q->pos_in_heap != NULL);
    assert(id >= 0);

    int pos = q->pos_in_heap[id];
    if (pos == -1) {
        /* not present: insert */
        priority_queue_push(q, id, new_val);
        return;
    }

    float old = q->heap[pos].val;
    q->heap[pos].val = new_val;

    if (new_val < old) {
        sift_up(q, pos);
    } else if (new_val > old) {
        sift_down(q, pos);
    }
}
