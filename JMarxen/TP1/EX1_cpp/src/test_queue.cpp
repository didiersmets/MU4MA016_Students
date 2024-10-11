#include <stdio.h>
#include <stdlib.h>

#include "circular_buffer_queue.h"

int main(int argc, char* argv[]) {
	size_t capacity = 5;
	Queue<int> q(capacity);
	size_t n = atoi(argv[1]);
	size_t l_max = q.get_length();
	srand(1);
	for (int i = 0; i < n; i++) {
		// printf("Step %d:\n", i);
		int p = rand() % 100;
		if (p % 2 == 0) {
			q.enqueue(p);
		} else {
			q.dequeue();
		}
		// printf("p:%d \n", p);
		if (l_max < q.get_length()) {
			l_max = q.get_length();
		}
		// printf("l_max:%zu \n", l_max);
		// printf("l:%zu \n", queue_length(q));
		// print_queue(q);
	}
	printf("%zu\n", l_max);
	return l_max;
}

