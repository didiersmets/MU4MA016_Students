#include <stdio.h>
#include <stdlib.h>
#include <priority_queue.h>

int priority_queue_init(struct priority_queue* q, int max_id)
{
	q->capacity = 8;
	q->size = 0;
	q->heap = (struct priority_data)malloc(q->capacity*sizeof(priority_data));
	q->pos_in_heap = (int*)malloc(max_id * sizeof(int));
}

static void swap(struct priority_queue* q, int pos1, int pos2)
{
	struct priority_data temp;
	int id1 = q->data[pos1].id;
	int id2 = q->data[pos2].id
	temp = q->data[pos1];
	q->data[pos1] = q->data[pos2];
	q->data[pos2] = temp;
	q->pos_in_heap[id1] = pos2;
	q->pos_in_heap[id2] = pos1;
}

static void sift_up(struct priority_queue* q, int pos)
{
	swap(q, pos, (pos - 1) / 2);
}

static void sift_down(struct priority_queue* q, int pos)
{
	swap(q, pos, 2 * pos + 1);
}

static void enlarge_capacity(struct priority_queue* q)
{
	q->capacity *= 2;
	q->data = realloc(q->data, sizeof(struct priority_queue) * q->capacity);
}

void priority_queue_push(struct priority_queue* q, int id, float val)
{
	if (q->size == q->capacity)
		enlarge_capacity(q);
	struct priority_data d;
	d.id = id;
	d.val = val;
	q->data[q->size] = d;
	int i = q->size;
	q->size ++;
	while(i > 0)&&(q->data[i].val < q->data[(i - 1)/2].val){
		sift_up(q, i);
		i = (i - 1)/2;
	}
}

struct priority_data priority_data_pop(struct priority_queue* q)
{
	struct priority_data pop;
	pop = q->data[0];
	q->size --;
	q->data[0] = q->data[q->size];
	int i = 0;
	while(i < q->size)&&((q->data[i].val > q->data[2 * i + 1].val)||(q->data[i].val > q->data[2 * (i + 1)].val)){
		sift_down(q, i);
		i = 2 * j + 1;
	}
	return pop;
}

void priority_queue_update(struct priority_queue* q, int key, float new_val);






