

struct priority_data {
    int id;    //unique identifier
    float val;   //priority value
};


struct priority_queue {
    struct priority_data *heap;
    int capacity;
    int size;
    int *pos_in_heap;
};


//int priority_queue_init(struct priority_queue *q, int capactiy);  //ex 2
void priority_queue_push(struct priority_queue *q, int id, float val);
struct priority_data priority_queue_pop(struct priority_queue *q);
int priority_queue_init(struct priority_queue *q, int max_id);
void priority_queue_update(struct priority_queue *q, int key, float new_val);