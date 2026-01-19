#include "prio_q.h"
#include <stdlib.h>
#include <stdio.h>

static void swap(struct priority_queue *q, int pos1, int pos2)
{
    int id1 = q->heap[pos1].id;
    int id2 = q->heap[pos2].id;

    struct priority_data tmp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = tmp;

    q->pos_in_heap[id1] = pos2;
    q->pos_in_heap[id2] = pos1;
}

static void sift_up(struct priority_queue *q, int pos)
{
    while (pos > 0)
    {
        int parent = (pos - 1) / 2;
        if (q->heap[parent].val <= q->heap[pos].val)
            break;
        swap(q, parent, pos);
        pos = parent;
    }
}

static void sift_down(struct priority_queue *q, int pos)
{
    while (1)
    {
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

static int ensure_capacity(struct priority_queue *q)
{
    if (q->size < q->capacity)
        return 1;

    int newcap = q->capacity * 2;
    struct priority_data *newheap =
        (struct priority_data *)realloc(q->heap, sizeof(struct priority_data) * newcap);

    if (!newheap)
        return 0;

    q->heap = newheap;
    q->capacity = newcap;
    return 1;
}

int priority_queue_init(struct priority_queue *q, int max_id)
{
    q->capacity = 16;
    q->size = 0;

    q->heap = (struct priority_data *)malloc(sizeof(struct priority_data) * q->capacity);
    if (!q->heap)
        return 0;

    q->pos_in_heap = (int *)malloc(sizeof(int) * (max_id + 1));
    if (!q->pos_in_heap)
    {
        free(q->heap);
        q->heap = NULL;
        return 0;
    }

    for (int i = 0; i <= max_id; i++)
        q->pos_in_heap[i] = -1;
    return 1;
}

void priority_queue_free(struct priority_queue *q)
{
    free(q->heap);
    free(q->pos_in_heap);
    q->heap = NULL;
    q->pos_in_heap = NULL;
    q->capacity = 0;
    q->size = 0;
}

void priority_queue_push(struct priority_queue *q, int id, float val)
{
    if (q->pos_in_heap[id] != -1)
    {
        priority_queue_update(q, id, val);
        return;
    }

    if (!ensure_capacity(q))
    {
        fprintf(stderr, "priority_queue_push: realloc failed\n");
        exit(1);
    }

    int pos = q->size;
    q->heap[pos].id = id;
    q->heap[pos].val = val;
    q->pos_in_heap[id] = pos;

    q->size++;
    sift_up(q, pos);
}

struct priority_data priority_queue_pop(struct priority_queue *q)
{
    if (q->size == 0)
    {
        fprintf(stderr, "priority_queue_pop: empty queue\n");
        exit(1);
    }

    struct priority_data res = q->heap[0];
    q->pos_in_heap[res.id] = -1;

    q->size--;
    if (q->size > 0)
    {
        q->heap[0] = q->heap[q->size];
        q->pos_in_heap[q->heap[0].id] = 0;
        sift_down(q, 0);
    }

    return res;
}

void priority_queue_update(struct priority_queue *q, int key, float new_val)
{
    int pos = q->pos_in_heap[key];
    if (pos == -1)
    {
        return;
    }

    float old = q->heap[pos].val;
    q->heap[pos].val = new_val;

    if (new_val < old)
        sift_up(q, pos);
    else if (new_val > old)
        sift_down(q, pos);
}
