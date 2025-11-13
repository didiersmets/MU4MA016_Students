#include <stdio.h>
#include <stdlib.h>

#include "../include/priority_queue.h"

int priority_queue_init(struct priority_queue *q, int capacity, int max_id){
    q->size = 0;
    q->capacity = capacity;
    q->heap = (struct priority_data *)malloc(capacity*sizeof(struct priority_data));
    q->pos_in_heap = (int *)malloc((max_id + 1)* sizeof(int));

    //initialising all entries of pos_in_heap to -1
    for(int i = 0; i < max_id; i++){
        (q->pos_in_heap)[i] = -1;
    }
    
    return 0;
}

//--------------------------------------------------------------------
static void sift_up(struct priority_queue *q, int pos);
static void sift_down(struct priority_queue *q, int pos);
//--------------------------------------------------------------------
void priority_queue_push(struct priority_queue *q, int id, float val){

    struct priority_data elt = {id, val};

    if(q->size < q->capacity){
        (q->heap)[q->size] = elt;
        (q->pos_in_heap)[id] = q->size;
        q->size++;
        sift_up(q, q->size);
    }else{
        printf("The heap is full !\n");
    }
}

//--------------------------------------------------------------------
struct priority_data priority_queue_pop(struct priority_queue *q){
    if(q->size == 0){
        printf("No node to pop! Push an element first.\n");
        exit(1);
    }

    int pos = 0;    //we pop the root
    struct priority_data pop = (q->heap)[pos];

    //"Lower-right" node moved in place of old root
    (q->heap)[pos] = (q->heap)[q->size - 1];
    
    //Update the positions and size
    (q->pos_in_heap)[pop.id] = -1;
    (q->pos_in_heap)[(q->heap)[0].id] = 0;
    q->size--;

    sift_down(q, 0);

    return pop;
}

//--------------------------------------------------------------------
static void swap(struct priority_queue *q, int pos1, int pos2){

    struct priority_data tmp = (q->heap)[pos1];
    (q->heap)[pos1] = (q->heap)[pos2];
    (q->heap)[pos2] = tmp;

    (q->pos_in_heap)[(q->heap)[pos1].id] = pos1;
    (q->pos_in_heap)[(q->heap)[pos2].id] = pos2;
}

//--------------------------------------------------------------------
static int parent(int index){return (index - 1)/2;}

//--------------------------------------------------------------------
static int left_child(int index){return 2*index + 1;}

//--------------------------------------------------------------------
static int right_child(int index){return 2*index + 2;}

//--------------------------------------------------------------------
static void sift_up(struct priority_queue *q, int pos){
    
    while(pos != 0 && (q->heap)[pos].val > (q->heap)[parent(pos)].val){
        int parent_pos = parent(pos);
        swap(q, pos, parent_pos);
        pos = parent_pos;
    }
}

//--------------------------------------------------------------------
static void sift_down(struct priority_queue *q, int pos){

    int left_pos = left_child(pos);
    int right_pos = right_child(pos);
    int max_child;

    //Find child with biggest key
    if(left_pos >= q->size && right_pos >= q->size){    //No child => no sift down
        return;
    }else if(right_pos >= q->size){                     //Only left child
        max_child = left_pos;
    }else{                                              //Two children
        max_child = (q->heap)[right_pos].val > (q->heap)[left_pos].val ? right_pos : left_pos;
    }

    int max_prio_child = (q->heap)[max_child].val;

    while((q->heap)[pos].val < max_prio_child){

        swap(q, pos, max_child);
        pos = max_child;

        //Update child with biggest key
        left_pos = left_child(pos);
        right_pos = right_child(pos);

        if(left_pos >= q->size && right_pos >= q->size){    //No child => no sift down
            return;
        }else if(right_pos >= q->size){                     //Only left child
            max_child = left_pos;
        }else{                                              //Two children
            max_child = (q->heap)[right_pos].val > (q->heap)[left_pos].val ? right_pos : left_pos;
        }

        max_prio_child = (q->heap)[max_child].val;
    }
}

//--------------------------------------------------------------------
void priority_queue_update(struct priority_queue *q, int key, float new_val){
    int pos = (q->pos_in_heap)[key];
    (q->heap)[pos].val = new_val;
}