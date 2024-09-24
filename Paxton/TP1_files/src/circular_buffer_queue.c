#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"circular_buffer_queue.h"
#include <stdbool.h>


static void enlarge_queue_capacity ( struct Queue *q){
    q->capacity*=2;
};

bool is_empty(const struct Queue *q){// the function returns bool 'true' is the queue is indeed empty
    if(q->length ==0 || q->data==NULL){
        return true;
    }
    return false;
};

size_t queue_length(const struct Queue *q){
    return q->length;
};

int queue_init(struct Queue *q, size_t elem_size, size_t capacity){
    q->capacity=capacity;
    q->elem_size= elem_size;
    q->data=malloc(elem_size*capacity);
    if (q->data==NULL){return -1;}//-1 is the error code
    q->length=0;
    q->front=0;
    return 0;//0 is success.
};



void queue_dispose(struct Queue *q){
    if (is_empty(q)){return;}
    if (q->data!=NULL){
        
    }
};

void queue_enqueue(struct Queue *q, const void *src);

void queue_dequeue(struct Queue *q, void *dest);


int main(int argc, char** argv){
    printf("Hello000 testinggg");
    return 0;
}