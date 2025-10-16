#include <stdbool.h>
#include <stddef.h> // for size_t
#include <circular_buffer_queue.hpp>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    int l_max = 0;
    int n = atoi(argv[1]); //number of random integers
    struct Queue<int> *q = queue_init<int>(n);
    for(int i=0; i < n; i++){
        int p = rand();
        if(p%2 == 0){
            queue_enqueue<int>(q, &p);
        }
        else{
            int g = 0;
            queue_dequeue<int>(q, &g);
        }
        if(q->length > l_max){
            l_max = q->length;
        }
    }
    printf("l_max: %d\n",l_max);
    queue_dispose<int>(q);
    return l_max;
}