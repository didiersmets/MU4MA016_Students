#include <stdio.h>
#include <stdlib.h>

#include "circular_buffer_queue.h"

void print_queue(struct Queue*);

int main(int argc, char* argv[]) {
	size_t elem_size = sizeof(int);
	size_t capacity = 5;
	struct Queue* q = queue_init(elem_size, capacity);
	size_t n = atoi(argv[1]);
	size_t l_max = queue_length(q);
	srand(1);
	for (int i = 0; i < n; i++) {
		// printf("Step %d:\n", i);
		int p = rand() % 100;
		if (p % 2 == 0) {
			queue_enqueue(q, &p);
		} else {
			int dest;
			queue_dequeue(q, &dest);
		}
		// printf("p:%d \n", p);
		if (l_max < queue_length(q)) {
			l_max = queue_length(q);
		}
		// printf("l_max:%zu \n", l_max);
		// printf("l:%zu \n", queue_length(q));
		// print_queue(q);
	}
	printf("%zu\n", l_max);
	return l_max;
}

void print_queue(struct Queue* q) {
	for (int i = 0; i < q->capacity; i++) {
		int* elem = (int*)(q->data) + i;
		printf("%d\n", *elem);
	}
}
