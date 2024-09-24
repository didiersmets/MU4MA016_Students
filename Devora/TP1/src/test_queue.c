#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer_queue.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    size_t n = (size_t) atoi(argv[1]);
    struct Queue q;
    queue_init(&q, 0, n);
    printf("Capacity: %zu\n", n);

    queue_init(&q, sizeof(int), n);
    int l_max = 0;
    for (int i = 0 ; i < n; i++) {
        int random = rand() % 100;
        if (random % 2 == 0) {
            queue_enqueue(&q, &random);
        } else {
            int buffer;
            queue_dequeue(&q, &buffer);
            // printf("Buffer : %i", buffer);
        }
        int length = queue_length(&q);
        if (length > l_max ) {
            l_max = length;
            // printf("New l_max : %i", l_max);
        }
    }
    printf("Max observed length : %i", l_max);
    return 0;
}
