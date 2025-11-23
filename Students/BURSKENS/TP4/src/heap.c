#include <heap.h>
#include <stdlib.h>
#include <stdio.h>

int priority_queue_init(struct priority_queue *q){
    q->capacity = 0;
    q->size = 0;
    q->heap = NULL;
    return 0;
}

static void enlarge_queue_capacity (struct priority_queue *q){
    if(q->capacity == 0){
        q->capacity = 1;
        q->heap = malloc(sizeof(struct priority_data));
    }
    else{
        q->capacity = q->capacity * 2;
        q->heap=realloc(q->heap,q->capacity);
    }
}

static void swap(struct priority_queue *q, int pos1, int pos2){
    struct priority_data temp = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = temp;
}

static void sift_up(struct priority_queue *q, int pos){
    int current_position = pos;
    int parent = pos/2;
    while(pos > 0 && q->heap[parent]->val < q->heap[current_position]->val){  
        swap(q,current_position,parent);
        current_position = parent;
        parent = current_position/2;
    }
}

static void sift_down(struct priority_queue *q, int pos){
    int current_position = pos;
    int child1 = 2*pos + 1;
    int child2 = 2*pos + 2;
    while(child1 < q->size){
        int max_child = child1;
        if(child2 < q->size && q->heap[child2]->val > q->heap[child1]->val){
            max_child = child2;
        }
        if(q->heap[current_position]->val < q->heap[max_child]->val){
            swap(q,current_position,max_child);
            current_position = max_child;
            child1 = 2*current_position + 1;
            child2 = 2*current_position + 2;
        }
        else{
            break;
        }
    }
}

void priority_queue_push(struct priority_queue *q, int id, float val){
    if(q->size +1 > q->capacity){
        enlarge_queue_capacity(q);
    }
    int queue_end = q->size;
    q->size = queue_end + 1;
    struct priority_data entry = {id,val};
    q->heap[queue_end] = entry;
    sift_up(q,queue_end);
}
struct priority_data priority_queue_pop(struct priority_queue *q){
    if(q->size <= 0){
        return NULL;
    }
    else{
        int queue_end = q->size - 1;
        swap(q,0,queue_end);
        struct priority_data entry = q->heap[queue_end];
        q->size = queue_end;
        sift_down(q,0);
        return entry;
    }
}



