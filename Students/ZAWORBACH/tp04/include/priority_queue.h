struct priority_data{
    int priority;
    int data;
};

struct priority_queue{
    priority_data* heap;
    int capacity;
    int size;
};

int priority_queue_init ( struct priority_queue * q );
void priority_queue_push ( struct priority_queue *q , int id , float val );
struct priority_data priority_queue_pop ( struct priority_queue * q );

static void swap ( struct priority_queue *q , int pos1 , int pos2 );
static void sift_up ( struct priority_queue *q , int pos );
static void sift_down ( struct priority_queue *q , int pos );