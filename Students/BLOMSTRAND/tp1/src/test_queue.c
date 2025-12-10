#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/circular_buffer_queue.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n < 0)
        n = 0;

    srand((unsigned)time(NULL));

    struct Queue *q = queue_init(sizeof(int), 10);
    int max_length = 0;

    for (int i = 0; i < n; i++)
    {
        int p = rand();

        if (p % 2 == 0)
        {
            queue_enqueue(q, &p);
            int current_length = (int)queue_length(q);
            if (current_length > max_length)
            {
                max_length = current_length;
            }
        }
        else
        {
            if (!is_empty(q))
            {
                int dummy;
                queue_dequeue(q, &dummy);
            }
        }
    }

    printf("Max queue length observed: %d\n", max_length);
    queue_dispose(q);
    return max_length;
}
