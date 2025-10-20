#include <cstdlib>



/*------------------*/   
/*    First case    */  
/*------------------*/
struct priority_data{
    int id;
    float val;
}

struct priority_queue{
    struct priority_data* heap;
    int capacity;
    int size;
}




//Swap/sift_up/sift_down
static void swap(struct priority_queue *q, int pos1, int pos2){
    float tmp = q->heap[pos1].val;
    q->heap[pos1].val = q->heap[pos2].val;
    q->heap[pos2].val = tmp;

    struct priority_data tmp_data = q->heap[pos1];
    q->heap[pos1] = q->heap[pos2];
    q->heap[pos2] = tmp_data;
}

static void sift_up(struct priority_queue *q, int pos){
    
    int indice = pos;
    while(q->heap[indice].val > q->heap[(indice-1) / 2].val){
        swap(q, indice, (indice - 1) / 2);
        indice = (indice-1) / 2;
        if(indice < 0) break;
    }
}

static void sift_down(struct priority_queue *q, int pos){
    
    int indice = pos;
    while(q_tmp->heap[indice] < q_tmp->heap[2 * indice - 1]){
        swap(q, indice, 2 * indice - 1);
        indice = 2 * indice - 1;
        if(indice >= q->size) break;
    }
}




//Init/Push/Pop
int priotity_queue_init(struct priority_queue *q){
    q->heap = (struct priority_data*)malloc(sizeof(struct priority_data) * 10);
    q->capacity = 10;
    q->size = 0;
}

void priority_queue_push(struct priority_queue *q, int id, float val){
    if(q->capacity == q->size){
        struct priority_data* tmp = (struct priority_data*)malloc(sizeof(struct priority_data) * q->capacity * 2);
        for(int i = 0; i < p->capacity; i++){
            tmp[i] = q->heap[i];
        }
        q->heap = tmp;
        q->capacity = q->capacity * 2;
    }

    struct priority_data new_p;
    new_p.val = val;
    new_p.id = id;
    q->heap[q->size]=new_p;

    int indice = q->size;
    sift_up(q, indice);
}

struct priority_data priority_queue_pop(struct priority_queue *q){
    struct priority_queue* q_tmp;
    struct priority_data* tmp = (struct priority_data*)malloc(sizeof(struct priority_data) * q->capacity * 2);
    for(int i = 0; i < p->capacity; i++){
        tmp[i] = q->heap[i];
    }
    q_tmp->heap = tmp;
    q_tmp->capacity = q->capacity;
    q_tmp->size = q->size;
    
    swap(q_tmp, 0, q->size)
    int indice = 0;
    sift_down(q_tmp, indice);
    q_tmp->size--;
    return q_tmp;
}



/*-------------------*/   
/*    Second case    */  
/*-------------------*/
struct priority_queue2{
    struct priority_data* heap;
    int capacity;
    int size;
    int *pos_in_heap;
}

int priority_queue_init2(struct priority_queue2 *q, int max_id){
    q->heap = (struct priority_data*)malloc(sizeof(struct priority_data) * 10);
    q->capacity = 10;
    q->size = 0;
    q->pos_in_heap = (int*)malloc(sizeof(int) * (max_id + 1));
    for(int i = 0; i < max_id+1; i++){
        q->pos_in_heap[i] = -1;
    }
}

void priority_queue_push2(struct priority_queue2 *q, int id, float val){
    if(q->capacity == q->size){
        struct priority_data* tmp = (struct priority_data*)malloc(sizeof(struct priority_data) * q->capacity * 2);
        for(int i = 0; i < p->capacity; i++){
            tmp[i] = q->heap[i];
        }
        q->heap = tmp;
        q->capacity = q->capacity * 2;
    }

    struct priority_data new_p;
    new_p.val = val;
    new_p.id = id;
    q->heap[q->size]=new_p;

    int indice = q->size;
    while(q->heap[indice].val > q->heap[(indice-1) / 2].val){
        sift_up(q, indice);
        indice = (indice-1) / 2;
        if(indice < 0) break;
    }
}

struct priority_data priority_queue_pop2(struct priority_queue2 *q){
    struct priority_queue2* q_tmp;
    struct priority_data* tmp = (struct priority_data*)malloc(sizeof(struct priority_data) * q->capacity * 2);
    for(int i = 0; i < p->capacity; i++){
        tmp[i] = q->heap[i];
    }
    q_tmp->heap = tmp;
    q_tmp->capacity = q->capacity;
    q_tmp->size = q->size;
    
    swap(q_tmp, 0, q->size)
    int indice = 0;
    while(q_tmp->heap[indice] < q_tmp->heap[2 * indice - 1]){
        sift_down(q_tmp, indice);
        indice = 2 * indice - 1;
        if(indice >= q->size) break;
    }
    q_tmp->size--;
    return q_tmp;
}