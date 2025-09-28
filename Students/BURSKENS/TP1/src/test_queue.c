#include <stdbool.h>
#include <stddef.h> // for size_t
#include <circular_buffer_queue.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    int l_max = 0;
    int n = atoi(argv[1]); //number of random integers
    struct Queue *q = queue_init(sizeof(int), n);
    for(int i=0; i < n; i++){
        int p = rand();
        if(p%2 == 0){
            queue_enqueue(q, &p);
        }
        else{
            int g = 0;
            queue_dequeue(q, &g);
        }
        if(q->length > l_max){
            l_max = q->length;
        }
    }
    printf("l_max: %d\n",l_max);
    queue_dispose(q);
    return l_max;
}
