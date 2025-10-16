#include "../include/circular_buffer_queue_cpp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){

    if(argc < 2){
        printf("Please give an integer ! \n");
        return 1;
    }

    size_t n = atoi(argv[1]);

    struct Queue<int> *q = queue_init<int>(n);

    size_t l_max = queue_length(q);
    srand(time(NULL));

    for(int i = 0; i<n; i++){

        int p = rand();

        if(p % 2 == 0){
            queue_enqueue(q, &p);
        }else{
            int disposed;
            queue_dequeue(q,&disposed);
        }

        if(q->length > l_max){
            l_max = queue_length(q);
        }
    }

    queue_dispose(q);
    printf("l_max is %ld \n", l_max);
    return l_max;
}