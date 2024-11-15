#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"

int main(int argc, char* argv[]) {
	struct priority_queue q;
	priority_queue_init(&q, 10);
	priority_queue_push(&q, 1, 5.0);
	priority_queue_push(&q, 2, 10.0);
	priority_queue_push(&q, 3, 3.0);
	priority_queue_push(&q, 4, 8.0);
	printf("Top element (expected id=2): id=%d, val=%.1f\n", q.heap[0].id,
	       q.heap[0].val);
	// Update priority of element with id = 3 to a higher value
	priority_queue_update(&q, 3, 15.0);
	printf(
	    "After update, new top element (expected id=3): id=%d, val=%.1f\n",
	    q.heap[0].id, q.heap[0].val);
	// Pop elements to test order
	while (q.size > 0) {
		struct priority_data top = priority_queue_pop(&q);
		printf("Popped element: id=%d, val=%.1f\n", top.id, top.val);
	}
	free(q.heap);
	free(q.pos_in_heap);
	return 0;
}
