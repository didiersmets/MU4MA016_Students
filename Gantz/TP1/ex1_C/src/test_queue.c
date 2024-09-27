#include <stdlib.h>
#include <stdio.h>

#include "../include/circular_buffer_queue.h"

typedef struct Queue Q;

int main(int argc, char* argv[]){
	
	Q* q = queue_init(sizeof(int),5);

	int length_max = 0;

	int n = atoi(argv[1]);
	
	for(int i=0; i<n; i++){
		
		int rand_value = rand();
		printf("%d\n",rand_value);

		if(rand_value%2==0){
			printf("-> enqueue\n");
			queue_enqueue(q,&rand_value);
		} else {
			printf("-> dequeue\n");
			void* dest = malloc(sizeof(int));
			queue_dequeue(q,dest);
			free(dest);
		}

		length_max = q->length > length_max ? q->length : length_max;
		printf("length-max: ");
		printf("%d\n", length_max);
		printf("--------------------\n");
	}

	return 0;

}
