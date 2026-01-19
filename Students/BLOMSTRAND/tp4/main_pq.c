#include "prio_q.h"
#include <stdio.h>

int main(void)
{
    struct priority_queue q;

    if (!priority_queue_init(&q, 100))
    {
        printf("init failed\n");
        return 1;
    }

    priority_queue_push(&q, 1, 5.0f);
    priority_queue_push(&q, 2, 3.0f);
    priority_queue_push(&q, 3, 9.0f);

    priority_queue_update(&q, 3, 1.0f);

    while (q.size > 0)
    {
        struct priority_data x = priority_queue_pop(&q);
        printf("pop: id=%d val=%f\n", x.id, x.val);
    }

    priority_queue_free(&q);
    return 0;
}
