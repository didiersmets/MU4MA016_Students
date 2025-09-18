#include "circular_buffer_queue.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please provide exactly 1 positive integer.\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Please enter a positive number.\n");
        return 1;
    }

    struct Queue<int> *q = queue_init<int>(2);
    
    int max_length = 0;

    for (int i = 0; i < n; i++) {
        int value = rand();

        if (value % 2 == 0) {
            queue_enqueue(q, &value);
            printf("Enqueued %d\n", value);

            if (queue_length(q) > max_length) {
                max_length = queue_length(q);
            }
        } else {
            int dequeued_value;
            queue_dequeue(q, &dequeued_value);
            printf("Dequeued %d\n", dequeued_value);
        }
    }

    queue_dispose(q);
    printf("Max queue length reached: %d\n", max_length);
    return 0;
}