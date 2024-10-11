#include <stdio.h>
#include <stdlib.h>

#include "circular_buffer_queue.h"


int random_q(int n)
{
 
  struct Queue *q=queue_init(sizeof(int),n);
  size_t l_max = q->length;

  for (int i =0; i < n; i++){
    int p = rand();
    if ((p % 2) == 0){
      queue_enqueue(q,&p);
    } else {
      void *dest=malloc(sizeof(int));
      queue_dequeue(q,dest);
      free(dest);
    };
    if(queue_length(q) > l_max){
      l_max = q -> length;
    };
  };
  return l_max;
};

int main()
{
  int n;
  printf("please input the number : \n");
  scanf("%d",&n);
  printf("the largest length : %d \n",random_q(n));
  return 0;
};  
