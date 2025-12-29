#include "tp4.h"

#include <stdio.h>
#include <stdlib.h>

//swap two elements in heap 
static void swap(struct priority_queue *q, int pos1, int pos2){
    struct priority_data temp = q->heap[pos2];
    q->heap[pos2] = q->heap[pos1];
    q->heap[pos1] = temp;
    //for both pos switch pos in heap
    q->pos_in_heap[q->heap[pos1].id] = pos1;
    q->pos_in_heap[q->heap[pos2].id] = pos2;
}


static void sift_up(struct priority_queue *q, int pos){
    int  parent = (pos - 1) / 2;
    //val of parent has to be smaller than value of child
    while(pos > 0 && (q->heap[parent].val < q->heap[pos].val)){
        swap(q, pos, parent);
        pos = parent;
        parent = (pos - 1) / 2;
    }
}


static void sift_down_pop(struct priority_queue *q, int pos){
    int l = 2 * pos + 1; //left child
    int r = 2 * pos + 2; //right child

    //if l > pos of the last element, then also r > --> no children
    while (l <= (q->size)-1){
        if(r > (q->size)-1 || q->heap[l].val > q->heap[r].val){
            swap(q, pos, l);
            pos = l;
        }
        else{
            swap(q, pos, r);
            pos = r;
        }
        l = 2 * pos + 1;
        r = 2 * pos + 2;
    }
    q->heap[pos] = q->heap[(q->size)-1];
    q->pos_in_heap[q->heap[(q->size)-1].id] = pos;
    sift_up(q, pos);
}

static void sift_down(struct priority_queue *q, int pos){
    int l = 2 * pos + 1; //left child
    int r = 2 * pos + 2; //right child

    while ((l <= (q->size)-1 && (q->heap[pos].val < q->heap[l].val) || 
            (r <= (q->size)-1 && q->heap[pos].val < q->heap[r].val))){
        //if parent has no right child and left child ist bigger than parent or 
        //if left child is bigger than right child and right child exists
        if((r >= (q->size) && q->heap[pos].val < q->heap[l].val) || ((r < (q->size)-1 && q->heap[l].val > q->heap[r].val) && q->heap[pos].val < q->heap[l].val)){
            swap(q, pos, l);
            pos = l;
        }
        //right exists and bigger than 
        else{
            swap(q, pos, r);
            pos = r;
        }
        l = 2 * pos + 1;
        r = 2 * pos + 2;
    }
}
/* ex 2
int priority_queue_init(struct priority_queue *q, int capacity){
    q->heap = malloc(capacity * sizeof(struct priority_data));
    q->capacity = capacity;
    q->size = 0;

    return 0;
}*/


void priority_queue_push(struct priority_queue *q, int id, float val){
    if(q->size == q->capacity){
        printf("Push not possible, no free slot in queue");
        return;
    }
    q->heap[q->size].id = id;
    q->heap[q->size].val = val;
    //ad pos in heap --> last element in array when pushed
    q->pos_in_heap[id] = q->size;
    sift_up(q, q->size);
    q->size += 1;
}



int priority_queue_init(struct priority_queue *q, int max_id){
    q->heap = malloc((max_id + 1) * sizeof(struct priority_data));
    q->capacity = max_id + 1;
    q->size = 0;
    //new: add the pos in heap array
    q->pos_in_heap = malloc((max_id + 1) * sizeof(int));
    //and pre-fill with -1
    for (int i = 0; i < max_id+1; i++){
        q->pos_in_heap[i] = -1;
    }
    return 0;
}

struct priority_data priority_queue_pop(struct priority_queue *q){
    if(q->size == 0){
        printf("Caution, no element in queue");
        struct priority_data empty = {0, 0.0};
        return empty;
    }
    //to pop and return the root
    struct priority_data root = q->heap[0];
    //_________________________________________1st method
    //only works if modification of sift down
    //mark root as not present anymore
    //q->pos_in_heap[q->heap[0].id] = -1;
    //now add last element in queue to root
    //q->heap[0] = q->heap[q->size-1];
    //q->pos_in_heap[q->heap[0].id] = 0;  //find correct position
    //_____________________________________________________
    sift_down_pop(q, 0);
    //mark root as not present anymore
    q->pos_in_heap[root.id] = -1;
    q->size -= 1;
    return root;
}

void priority_queue_update(struct priority_queue *q, int key, float new_val){
    //goal: change value of some element in q
    //key: id of the element 
    int pos = q->pos_in_heap[key]; 
    q->heap[pos].val = new_val;
    sift_up(q, pos);
    sift_down(q, pos);
}

void priority_queue_dispose(struct priority_queue *q){
    free(q->heap);
    free(q->pos_in_heap);
    free(q);
}