#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include "circular_buffer_queue.h"

int main(int argc){
	int n = 4;
	struct Queue *q = malloc(sizeof(struct Queue));


	queue_init(q,sizeof(int),8);
	int l_max = 0;

	srand(time(NULL));
	int p;
	for(int i =0 ; i<n;i++){
		p = rand();
		if(p%2==0){
			queue_enqueue(q,&p);
		}else{ 
			queue_dequeue(q,&p);
		}
		if(q->length > l_max){
			l_max=q->length;
		}
	}
	printf("lenght == %d \n", l_max);
	queue_dispose(q);
	free(q);
	return 0;
}


