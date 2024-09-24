#include <stdlib.h>

#include "../include/circular_buffer_queue.h"

typedef struct Queue Q;

int main(int argc, char* argv[]){
	
	Q* q = queue_init(sizeof(int),5);

	int length_max = 1;

	int n = atoi(argv[1]);
	
	for(int i=0; i<n; i++){
		
		int rand_value = rand();

		if(rand_value%2==0){
			queue_enqueue(q,rand_value);
		} else {
			void* dest = malloc(sizeof(int));
			queue_dequeue(q,dest);
			free(dest);

		}

		length_max = q->length > length_max ? q->length : length_max;
	}

	return length_max;

}
