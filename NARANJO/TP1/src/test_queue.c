#include <stdio.h>
#include <stdlib.h>

int random_queue(int n){
	int l_max = 0
	struct Queue *q = queue_init(sizeof(int), n);
	for (int i; i < n; i++){
		int p = rand();
		if (p%2 == 0){
			queue_enqueue(q, p);
		}
		else{
			int dummy;
			queue_dequeue(q, dummy);
		}
		if queue_length(q) > l_max{
			l_max = queue.length(q);
		}
	}
	return l_max;
}
