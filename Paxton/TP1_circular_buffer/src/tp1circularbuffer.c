#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h> 
#include "circular_buffer_queue.h"
#include<assert.h>




int main(int argc, char** argv){
    int n=atoi(argv[1]);
    struct Queue q;
    int working = queue_init(&q, sizeof(int), 0);
    assert(!working);
    srand(time(NULL)); 
    int random_number; 
    int l_max=0;
    for (int i = 0; i<n; i++){
        random_number= rand() % 20 + 1;
        if(!(random_number%2)){
            queue_enqueue(&q, &random_number);
            l_max=queue_length(&q)>l_max ? queue_length(&q) : l_max; // is this beneficial            
        }
        else{
            int deq_element;
            queue_dequeue(&q ,&deq_element);
        }

    }

    printf("The max length is: %d", l_max);
    return 0;
}