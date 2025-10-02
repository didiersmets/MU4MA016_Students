#include "circular_buffer_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    int n;
    printf("Number of random integers");
    scanf("%d", &n);

    int l_max = 0;
    struct Queue *q = queue_init(sizeof(int), n);   /*use smaller capacity to test enlarge*/
    srand(time(NULL));  /*cf CM --> for different randoms*/

    for (int i = 0; i<n; i++){
        int p = rand();
        //printf("%d\t%d\t", p,i);
        //if even, enqueue
        if(p%2 == 0){                  
            queue_enqueue(q, &p);
        //if odd, dequeue
        }else{  
            int desti;
            queue_dequeue(q, &desti);
        }
        //always check l_max
        if(queue_length(q) > l_max){ 
            l_max = queue_length(q);
        }
        //printf("%d\n", l_max);  
    }
    queue_dispose(q);
    printf("%d", l_max);
    return l_max;
}