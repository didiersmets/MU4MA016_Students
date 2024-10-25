#include<stdbool.h>
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<circular_buffer_queue.h>


int main() {
	struct Queue* queue =  queue_init(sizeof(int), 10);
	
	int n;
	printf("Enter number of iterations please\n");
	scanf("%d", &n);
	getchar();

	int l_max = 0;
	for(int i = 0; i < n; i++){
		int p = rand();
		if(p%2 == 0){
			queue_enqueue(queue, &p);
			if (queue_length(queue) > l_max) {
				l_max = queue_length(queue);
			}
		} else {
			int dummy;
			queue_dequeue(queue, &dummy);
		}
	}
	printf("Max length : %d\n", l_max);
	
	return  l_max;
}




