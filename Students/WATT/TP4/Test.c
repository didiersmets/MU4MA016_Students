#include "Priority_Queue.h"
#include <stdio.h>

int main(void)
{
    struct priority_queue q;
    if (priority_queue_init(&q, 100) != 0) {
        printf("init failed\n");
        return 1;
    }

    priority_queue_push(&q, 10, 5.0f);
    priority_queue_push(&q, 20, 2.0f);
    priority_queue_push(&q, 30, 8.0f);

    /* Decrease-key (should move id=30 up) */
    priority_queue_update(&q, 30, 1.5f);

    while (q.size > 0) {
        struct priority_data x = priority_queue_pop(&q);
        printf("pop: id=%d val=%.3f\n", x.id, x.val);
    }

    priority_queue_free(&q);
    return 0;
}
