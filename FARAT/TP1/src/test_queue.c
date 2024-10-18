#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "circular_buffer_queue.c"



int main(int argc, char **argv){
	int t = atol(argv[1]);                            //argv[0] = nom de l'executable
	struct Queue *q = queue_init(sizeof(int), 10);
	int l_max = q->length;
	int i = 0;
	for (i=0; i<t; i++){
		int p = rand();
		if (p%2==0){queue_enqueue(q,&p);}
		else {
			if (q->length >0){queue_dequeue(q,&p);}}
		if (l_max < q->length){l_max = q->length;}
	}
	
	printf("la longueur maximal de la queue est : %d \n",l_max);
	free(q);
	return l_max;
}