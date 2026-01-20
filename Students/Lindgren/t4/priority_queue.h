#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct priority_data {
    int id;
    float val;
};

struct priority_queue {
    struct priority_data *heap;
    int capacity;
    int size;

    
    int *pos_in_heap;   
    int max_id;         
};


int  priority_queue_init(struct priority_queue *q, int max_id);

void priority_queue_destroy(struct priority_queue *q);

void priority_queue_push(struct priority_queue *q, int id, float val);

struct priority_data priority_queue_pop(struct priority_queue *q);

void priority_queue_update(struct priority_queue *q, int key, float new_val);

int  priority_queue_empty(const struct priority_queue *q);

#ifdef __cplusplus
}
#endif

#endif
