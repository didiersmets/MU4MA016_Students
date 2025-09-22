#include "circular_buffer_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t main(int argc, char **argv){

    int n = atoi(argv[1]);
    struct Queue *q = queue_init(sizeof(int), n);

    size_t l_max = q->length;
    srand(time(NULL));

    for(int i = 0; i<n; i++){

        int p = rand();
        //printf("p is %d\n", p);
        if(p % 2){
            queue_enqueue(q, &p);
        }else{
            void *dest;
            queue_dequeue(q,dest);
        }

        if(q->length > l_max){
            l_max = q->length;
        }
    }

    printf("l_max is %ld \n", l_max);
    return l_max;
}