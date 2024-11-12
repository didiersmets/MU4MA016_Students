#include "priority_queue.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int priority_queue_init(struct priority_queue *q, int max_id) {
	q->capacity = 10;
	q->size = 0;
	q->heap = malloc(q->capacity * sizeof(struct priority_data));
	q->pos_in_heap = malloc((max_id + 1) * sizeof(int));
	for (int i = 0; i <= max_id; i++) {
		q->pos_in_heap[i] = -1;
	}
	return 0;
}

void swap(struct priority_queue *q, int pos1, int pos2) {
	struct priority_data temp = q->heap[pos1];
	q->heap[pos1] = q->heap[pos2];
	q->heap[pos2] = temp;
	// Update positions in pos_in_heap
	q->pos_in_heap[q->heap[pos1].id] = pos1;
	q->pos_in_heap[q->heap[pos2].id] = pos2;
}

void sift_up(struct priority_queue *q, int pos) {
	int curr_pos = pos;
	int parent_pos = (pos - 1) / 2;
	while ((q->heap[curr_pos].val) > (q->heap[parent_pos].val)) {
		swap(q, curr_pos, parent_pos);
		curr_pos = parent_pos;
		parent_pos = (curr_pos - 1) / 2;
		if (parent_pos < 0) break;
	}
}

static void sift_down(struct priority_queue *q, int pos) {
	int left_child_pos = 2 * pos + 1;
	int right_child_pos = left_child_pos + 1;
	while (left_child_pos < q->size) {
		int l_b_r = (q->heap[left_child_pos].val) >
			    (q->heap[right_child_pos].val);
		int l_b_i = (q->heap[left_child_pos].val) > (q->heap[pos].val);
		int r_b_i = (q->heap[right_child_pos].val) > (q->heap[pos].val);
		if (l_b_r && l_b_i) {
			swap(q, left_child_pos, pos);
			pos = left_child_pos;
		} else if (!l_b_r && r_b_i) {
			swap(q, right_child_pos, pos);
			pos = right_child_pos;
		} else {
			break;
		}
		left_child_pos = 2 * pos + 1;
		right_child_pos = left_child_pos + 1;
	}
}

void priority_queue_push(struct priority_queue *q, int id, float val) {
	if (q->size >= q->capacity) {
		q->capacity *= 2;  // increase capacity if exceeding limit
		q->heap = realloc(q->heap,
				  q->capacity * sizeof(struct priority_data));
	}
	int pos = q->size++;
	q->heap[pos] = (struct priority_data){.id = id, .val = val};
	q->pos_in_heap[id] = pos;
	sift_up(q, pos);  // heapify by sifting up
}

struct priority_data priority_queue_pop(struct priority_queue *q) {
	if (q->size == 0)
		return (struct priority_data){.id = -1,
					      .val = 0};  // empty queue
	struct priority_data root = q->heap[0];
	q->pos_in_heap[root.id] = -1;	    // initialize root node to null
	q->heap[0] = q->heap[--(q->size)];  // replace root by last node
	q->pos_in_heap[q->heap[0].id] = 0;
	sift_down(q, 0);  // heapify by sifting new root down
	return root;
}

void priority_queue_update(struct priority_queue *q, int key, float new_val) {
	int pos = q->pos_in_heap[key];	// key = id of elem
	if (pos == -1) return;		// element not in the queue
	float old_val = q->heap[pos].val;
	q->heap[pos].val = new_val;
	// heapify
	if (new_val > old_val) {
		sift_up(q, pos);
	} else {
		sift_down(q, pos);
	}
}

