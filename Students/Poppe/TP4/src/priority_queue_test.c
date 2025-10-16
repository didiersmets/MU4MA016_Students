// gcc -o pq_test src/priority_queue.c src/priority_queue_test.c -Iinclude -std=c11

#include <stdlib.h>
#include <assert.h>
#include "priority_queue.h"

int main() {
    struct priority_queue pq;
    if (priority_queue_init(&pq, 100) != 0) {
        return -1; // Initialization failed
    }

    //small test
    priority_queue_push(&pq, 1, 5.0);
    priority_queue_push(&pq, 2, 3.0);
    priority_queue_push(&pq, 3, 8.0);

    struct priority_data pd = priority_queue_pop(&pq);
    assert(pd.id == 3 && pd.val == 8.0);
    pd = priority_queue_pop(&pq);
    assert(pd.id == 1 && pd.val == 5.0);
    pd = priority_queue_pop(&pq);
    assert(pd.id == 2 && pd.val == 3.0);

    //large test
    for(int i = 0; i < 100; i++) {
        priority_queue_push(&pq, i, (float)(i % 10));
    }
    for(int i = 9; i >= 0; i--) {
        for(int j = 0; j < 10; j++) {
            pd = priority_queue_pop(&pq);
            assert(pd.val == i);
        }
    }

    //test update
    for(int i = 0; i < 100; i++) {
        priority_queue_push(&pq, i, (float)(i % 10));
    }
    for(int i = 50; i < 60; i+=2) {
        priority_queue_update(&pq, i, 15.0f); // Increase priority
    }
    for(int i = 51; i < 60; i+=2) {
        priority_queue_update(&pq, i, -15.0f); // Decrease priority
    }

    for(int i = 0; i < 5; i++) {
        pd = priority_queue_pop(&pq);
        assert(pd.val == 15.0f);
    }
    for(int i = 9; i >= 0; i--) {
        for(int j = 0; j < 9; j++) {
            pd = priority_queue_pop(&pq);
            assert(pd.val == i);
        }
    }
    for(int i = 0; i < 5; i++) {
        pd = priority_queue_pop(&pq);
        assert(pd.val == -15.0f);
    }
    
    priority_queue_free(&pq);
    return 0;
}