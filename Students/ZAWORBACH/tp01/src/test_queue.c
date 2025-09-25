#include "../include/circular_buffer_queue.h"
#include <stdlib.h> // for malloc, free
#include <string.h> // for memcpy
#include <stdio.h>
  // for printf (debugging)
#include <time.h>
// main function to test the queue implementation
int main (int argc, char **argv){

    srand(time(NULL));
    int n = atoi(argv[1]);
    struct Queue *q = queue_init(sizeof(int), 4);
    int l_max = 0;
    int outt;

    for (int i=0; i<n; i++){
        int p = rand() % 100;
        printf("Enqueue %d\n", p);
        if (p % 2 == 0) {
            queue_enqueue(q, &p);
            if (q->length > l_max) {
                l_max = q->length;
            }
        }

        else {
            if (!is_empty(q)){
                queue_dequeue(q, &outt);
                printf("Dequeue %d\n", outt);
            }
        }
    }

    queue_dispose(q);

    printf("Max queue length: %d\n", l_max);
    return 0;
}   
