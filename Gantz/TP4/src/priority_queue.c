#include "../include/priority_queue.h"

#include <stdlib.h>

int priority_queue_init(struct priority_queue *q, int max_id){
	q->size = 0;
	q->capacity = 2;
	q->pos_in_heap = (int*) malloc((max_id+1)*sizeof(int));
	for(int i=0; i<max_id+1; i++) q->pos_in_heap[i]=-1;
	q->heap = (struct priority_data*) malloc(q->capacity*sizeof(struct priority_data));
	return 0;
}

static void swap(struct priority_queue *q, int pos1, int pos2){
	struct priority_data* h = q->heap;
	
	struct priority_data val1 = h[pos1];
	struct priority_data val2 = h[pos2];
	
	int id1 = val1.id;
	int id2 = val2.id;

	h[pos1] = val2;
	h[pos2] = val1;

	q->pos_in_heap[id1] = pos2;
	q->pos_in_heap[id2] = pos1;
}

static void sift_up(struct priority_queue *q, int pos){
	struct priority_data* h = q->heap;
	int parent = int((pos-1)/2);
	if(pos!=0 && (h[parent]).val<(h[pos]).val){
		swap(q,pos,parent);
		sift_up(q,parent);
	}
}

void priority_queue_push(struct priority_queue *q, int id, float val){
	if(q->size==q->capacity){
		q->capacity *= 2;
		q->heap = (struct priority_data*) realloc(q->heap, q->capacity);
	}
	struct priority_data data;
	data.id = id;
	data.val = val;
	q->heap[q->size] = data;
	q->pos_in_heap[id] = q->size;
	sift_up(q,q->size);
	q->size++;
}

static void sift_down(struct priority_queue *q, int pos){
	struct priority_data* h = q->heap;
	int left_child = 2*pos+1;
	int right_child = 2*pos+2;
	// case 1: there is a right child and therefore also a left child
	// case 2: there is only a left child
	// case 3: there are no children
	if(right_child < q->size){
		float left_child_val = h[left_child].val;
		float right_child_val = h[right_child].val;
		int swap_candidate = left_child_val > right_child_val ? left_child : right_child;
		if((h[pos]).val<(h[swap_candidate]).val){
			swap(q,pos,swap_candidate);
			sift_down(q,swap_candidate);
		}
	} else if(left_child < q->size){
		if((h[pos]).val<(h[left_child]).val){
			swap(q,pos,left_child);
			sift_down(q,left_child);
		}
	} else { // do nothing
	}

}

struct priority_data priority_queue_pop(struct priority_queue *q){
	struct priority_data* h = q->heap;
	struct priority_data root = h[0];
	q->pos_in_heap[root.id] = -1;
	swap(q,0,q->size);
	q->size--;
	sift_down(q,0);
	return root;
}

void priority_queue_update(struct priority_queue *q, int key, float new_val){
	q->heap[q->pos_in_heap[key]].val = new_val;
}


