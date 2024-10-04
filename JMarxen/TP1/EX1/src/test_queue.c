#include <stdlib.h>
#include <stdio.h>
#include "circular_buffer_queue.h"

void print_queue(struct Queue*);
	
int main() {
	size_t k = 10;
	size_t elem_size = sizeof(int);
	size_t capacity = k;
	struct Queue* q = queue_init(elem_size, capacity);
	size_t n = 20;
	size_t l_max=queue_length(q);
	for(int i=0; i<n;i++){
		int p = rand();
		if(p%2==0){
			queue_enqueue(q, &p);
		}
		else{
			int dest;
			queue_dequeue(q, &dest);
		}
		printf("p:%d \n", p); printf("l_max:%zu \n", l_max);
		if(l_max<queue_length(q)){l_max=queue_length(q);}
	}
	printf("%zu\n", l_max);
	return 0;
}

void print_queue(struct Queue* q){
	for(int i=0; i<q->capacity; i++){
		int *elem = (int *)(q->data)+i;
		printf("%d\n", *elem);
	}
}
