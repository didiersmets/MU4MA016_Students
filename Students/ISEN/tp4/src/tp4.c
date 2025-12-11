#include tp4.h

#include <stdio.h>
#include <stdlib.h>

static void swap(struct priority_queue *q, int pos1, int pos2){
    struct priority_data *temp = q->heap[pos2];
    q->heap[pos2] = q->heap[pos1];
    q->heap[pos1] = temp;
}


static void sift_up(struct priority_queue *q, int pos){
    int parent = (pos - 1) / 2;
    if(parent != 0){
        swap(q, pos, parent);
    }
    //not possible to sift up if its already the root
    else{
        printf("Sift up not possible");
        return;
    }
}


static void sift_down(struct priority_queue *q, int pos){
    //decide into which direction
    //swap the node with the one of its two children which has the highest value

}

int priority_queue_init(struct priority_queue *q, int capacity){
    q->heap = malloc(capacity * sizeof(struct priority_data));
    q->capacity = capacity;
    q->size = 0;
}


void priority_queue_push(struct priority_queue *q, int id, float val){
    if(q->size == q->capacity){
        printf("Push not possible, no free slot in tree");
        return;
    }
    struct priority_data *new;
    new->id = id;
    new->val = val;
}

struct priority_data priority_queue_pop(struct priority_queue *q){

}










struct priority_data priority_queue_pop(struct priority_queue *q){
    //idea: pop the highest 
}


static void swap(struct priority_queue *q, int pos1, int pos2){
    struct priority_data *temp = q[pos1];
    q->heap[pos1] = {q->heap[pos2].id , q->heap[pos2].val};
    q->heap[pos2] = {temp->id , temp->val };
}

static void sift_up(struct priority_queue *q, int pos){

}
static void sift_down(struct priority_queue *q, int pos){

}

//non recursive versions are potentially faster 
