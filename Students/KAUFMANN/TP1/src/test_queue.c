#include <stdlib.h>
#include <stdio.h>
#include "circular_buffer_queue.h"

size_t elem_size = sizeof(int);
size_t capacity = 100;

int main(int argc, char **argv) {

    int N = atoi(argv[1]);
    printf("N=%d\n", N);
    struct Queue *q = queue_init(elem_size, capacity);
    size_t length = 0;

    for (int i=0;i<N;i++) {
        int p = rand();
        if (p%2 == 0) {
            queue_enqueue(q, &p);
        }
        else {
            queue_dequeue(q, &p);
        }
        if (q->length > length) {
            length = q->length;
        }    
    }
    printf("%d\n", (int)length);
    return 0;
}
