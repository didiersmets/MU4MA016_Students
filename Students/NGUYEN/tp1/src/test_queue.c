#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "../include/circular_buffer_queue.h" 

/*
to compile : 
gcc circular_buffer_queue.c test_queue.c -I include -o test_queue

*/

int main(int argc, char **argv){
    int n = atoi(argv[1]);
    struct Queue *q = queue_init(sizeof(int), n);
    int l_max = queue_length(q);

    for (int i = 0; i<n; i++){
        int p = rand();
        if (p%2 == 0){
            queue_enqueue(q, &p);
        } else {
            if (queue_length(q) > 0){
                void *any;
                queue_dequeue(q, any);
            }
        }
        if (l_max < queue_length(q)){
            l_max = queue_length(q);
        }
    }
    printf("Largest lenght of the queue is : %d \n", l_max);
    queue_dispose(q);

    return 0;
}