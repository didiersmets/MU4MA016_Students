#include <stdlib.h>
#include <stdio.h>
#include "circular_buffer_queue.c"

int main(int argc, char**argv)
{
	struct Queue *q; 
	int p = rand;
	for (int i=0; i< argc; i++){
		if (p%2==0){
			queue_enqueue(q, p);
		}else{
			queue_dequeue(q);
		}
	}
	return q->length;
	queue_dispose(q);
}
