#include <stdio.h>
#include <stdlib.h>

#include "/root/MU4MA016_Students/ADrieux/TP4/heap_priority_queue.h"

int priority_queue_init(struct priority_queue *q, int max_id)
{
	q->capacity = 10;
	q->size = 0;
	q->heap = (struct priority_data *)malloc(q->capacity*sizeof(struct priority_data));
	q->pos_in_heap = (int *)malloc((max_id+1)*sizeof(int));
	for (int i = 0; i<max_id + 1; i++)
	{
		q->pos_in_heap[i] = -1;
	}
	return 0;
}

static void swap(struct priority_queue *q, int pos1, int pos2)
{
	struct priority_data key1 = q->heap[pos1];
	struct priority_data key2 = q->heap[pos2];

	int idx1 = key1.id;
	int idx2 = key2.id;

	q->heap[pos1] = key2;
	q->heap[pos2] = key1;

	q->pos_in_heap[idx1] = pos2;
	q->pos_in_heap[idx2] = pos1;
}

static void sift_up(struct priority_queue *q, int pos)
{
	while(q->heap[pos].val < q->heap[(pos - 1)/2].val)
	{
		swap(q, pos, (pos - 1)/2);
	}
}

static void sift_down(struct priority_queue *q, int pos) 
{
	struct priority_data left_child = q->heap[2*pos + 1];
	struct priority_data right_child = q->heap[2*pos + 2];
	while ((q->heap[pos].val > left_child.val) || (q->heap[pos].val > right_child.val))
	{
		if (lef_child.val < right_child.val)
		{
			swap(q, 2*pos + 1, pos);
		} else {
			swap(q, 2*pos + 2, pos);
		}
	}
}

void priority_queue_push(struct priority_queue *q, int id, float val)
{
	if (q->size >= q->capacity)
	{
		q->capacity = 2*q->capacity;
		q->heap = realloc(q->heap, q->capacity*sizeof(struct priority_data));
	}
	int tail = q->size;
	struct priority_data new_key;
	new_key.id = id;
	new_key.val = val;
	q->heap[tail] = new_key;
	q->pos_in_heap[id] = tail;
	sift_up(q, tail);
	q->size = tail + 1;
}

struct priority_data priority_queue_pop(struct priority_queue *q)
{
	struct priority_data root = q->heap[0];
	swap(q,0,q->size);
	q->size = q->size - 1;
	q->pos_in_heap[root.id] = -1;
	sift_down(q,0);
	return root;

}

void priority_queue_update(struct priority_queue *q, int key, float new_val)
{
	int pos = q->pos_in_heap[key];
	float old_val = q->heap[pos].val;
	if (pos == -1)
	{
		return;
	} else {
		q->heap[pos].val = new_val;
	}
	if (new_val < old_val)
	{
		sift_up(q, pos);
	} else {
		sift_down(q, pos);
	}
}




