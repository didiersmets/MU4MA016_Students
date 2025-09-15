#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer_queue.hpp"

int main(int argc, char* args[]) {
    if (argc != 2) {
        printf("Expected 1 argument (n)");
        return 1;
    }
    int n = atoi(args[1]);

    auto q = queue_init<int>(1);
    if (q == NULL) {
        printf("Queue initialization failed\n");
        return 1;
    }

    int l_max = 0;

    for (int i=0;i<n;i++) {
        int p = rand();
        if (p % 2 == 0) {
            queue_enqueue(q, &p);
        } else if (!is_empty(q)) {
            int val;
            queue_dequeue(q, &val);
        }
        if (queue_length(q) > l_max) {
            l_max = queue_length(q);
        }
    }

    printf("Max length: %d\n", l_max);
    queue_dispose(q);
}