#include <stdio.h>
#include <stdlib.h>
#include "../include/priority_queue.h"

int main(void) {
    struct priority_queue q;
    if (priority_queue_init(&q, 10) != 0) {
        fprintf(stderr, "failed to init priority queue\n");
        return 1;
    }

    printf("Pushing items: (id,val)\n");
    priority_queue_push(&q, 0, 1.0f);
    priority_queue_push(&q, 1, 5.0f);
    priority_queue_push(&q, 2, 3.0f);
    priority_queue_push(&q, 3, 4.5f);
    priority_queue_push(&q, 4, 2.2f);

    printf("Update id=4 to val=6.0 (should become top)\n");
    priority_queue_update(&q, 4, 6.0f);

    printf("Popping all items in order:\n");
    while (q.size > 0) {
        struct priority_data d = priority_queue_pop(&q);
        printf("id=%d val=%.2f\n", d.id, d.val);
    }

    /* pop from empty to see behavior */
    struct priority_data empty = priority_queue_pop(&q);
    printf("pop on empty returned id=%d val=%.2f\n", empty.id, empty.val);

    /* cleanup */
    free(q.heap);
    free(q.pos_in_heap);
    return 0;
}
