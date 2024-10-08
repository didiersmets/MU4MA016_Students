

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "circular_buffer_queue.h"


int main(int argc, char** argv) {
  int n = 10;         // initialize n=10 in case user to put args
  int p;
  size_t l_max = 0;

  if (argc > 1) {
    n = atoi(argv[1]); // number of successive random integers
  } 


  Queue *q = queue_init(sizeof(int), 10);
  for (int i=0; i<n; i++){
    p = rand();
    if (p%2 == 0) {
      queue_enqueue(q, &p) ;
      if (l_max < q->length) {l_max ++;}
    }
    else {queue_dequeue(q, &p);}
  }

  printf("%zu", l_max);

  return 0;
}



// gcc test_queue.c circular_buffer_queue.c -I ../include
