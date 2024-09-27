#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "circular_buffer_queue.h"

int main(int argc,int n){
	struct Queue *q;
	queue_init(q,sizeof(int),8);
	int *p;
	int *r;
	int l_max = 0;
	for(int i =0 ; i<n;i++){
		*p = rand();
		if(*p%2==0){
			queue_enqueue(q,p);
		}else{ 
			queue_dequeue(q,r);
		}
		if(q->length > l_max){
			l_max=q->length;
		}
	}
	return l_max;
}


