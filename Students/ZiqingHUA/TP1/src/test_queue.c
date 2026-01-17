#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "/users/home/28624202/MU4MA016_Students/ADrieux/TP1/include/circular_buffer_queue.h" 

int main(int argc, char** argv)
{
	struct Queue *q = queue_init(sizeof(int), 20);
	int l_max = queue_length(q);
	int n = atoi(argv[1]);
	srand(time(NULL));
	for (int i=0; i<n; i++)
	{
		int p = rand();
		if (p%2==0) {
			queue_enqueue(q,&p);
			printf("%d\n",p);
			l_max = l_max + 1;
		}else{
			queue_dequeue(q, &p);
		}
	}
	printf("%d\n", l_max);
	return 0;
	queue_dispose(q);
}

