#include <stdio.h>
#include <stddef.h>                // for size_t
#include "circular_buffer_queue.h" // Note the quotes, not angle brackets
#include <stdlib.h>                // needed for malloc
#include <string.h>                // for memcpy

int main(int argc, char *argv[])
{
    // argc = number of arguments
    // argv[0] = program name
    // argv[1] = first argument (the number n)
    if (argc != 2)
    {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }
    int num_of_integers = atoi(argv[1]);
    struct Queue *q = queue_init(sizeof(int), 10);
    int max_l = 0; // keep track of max length
    for (int i = 0; i < num_of_integers; i++)
    {
        int p = rand();
        if (p % 2 == 0)
        {
            queue_enqueue(q, &p);
            if (queue_length(q) > max_l)
            {
                max_l = queue_length(q);
            }
        }
        else
        {
            int dummy;
            queue_dequeue(q, &dummy);
        }
    }
    queue_dispose(q);

    printf("Maximum queue length: %d\n", max_l);
    return max_l;
}
