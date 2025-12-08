// src/test_queue.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/circular_buffer_queue.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    long n = strtol(argv[1], NULL, 10);
    if (n <= 0) {
        fprintf(stderr, "n must be positive\n");
        return 1;
    }

    struct Queue *q = queue_init(sizeof(int), 4);

    srand((unsigned)time(NULL));

    size_t l_max = 0;
    for (long i = 0; i < n; ++i) {
        int p = rand();
        if ((p % 2) == 0) {
            queue_enqueue(q, &p);
        } else {
            int tmp;
            queue_dequeue(q, &tmp);
        }
        if (q->length > l_max) l_max = q->length;
    }

    printf("%zu\n", l_max);
    free(q->data);
    free(q);
    return (int)l_max;
}
