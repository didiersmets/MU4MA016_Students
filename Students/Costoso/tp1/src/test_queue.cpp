#include "circular_buffer_queue.hpp"
#include <cstdlib>

int main(){
    int n=10;
    int l_max=0;
    size_t elem_size_=10;
    size_t capacity_=10;
    Queue *q = queue_init(elem_size_,capacity_);
    for( int i ; i < n ; i++ ){
        size_t p = rand();
        if(p%2 == 0){queue_enqueue(q,&p);}
        else{queue_dequeue(q,&p);}
        if(queue_length(q)>l_max){l_max=queue_length(q);}
    }
    return l_max;
}