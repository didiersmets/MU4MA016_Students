#include <stdio.h>
#include <circular_buffer_queue.h>
#include <stdlib.h>


int main(){
	Queue<int> q;
	int p = q[rand() % q.lenght];
  if (p%2==0) {
    queue_enqueue(q,p);
  	}	
  else {
    queue_dequeue();
  }
  return 0;
}


