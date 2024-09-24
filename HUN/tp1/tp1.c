
#include<stdbool.h>
#include<stddef.h>  // for size_t

typedef struct {
	size_t front;	   // index of the first element in the queue
	size_t length;	   // number of items presently in the queue
	size_t capacity;   // capacity of the queue (in nbr of items)
	size_t elem_size;  // length in bytes of each item in the queue
	void *data;	   // address of the array
} Queue ;

bool is_empty(const Queue *q);

size_t queue_length(const Queue *q);

int queue_init(Queue *q, size_t elem_size, size_t capacity);

void queue_dispose(Queue *q);

void queue_enqueue(Queue *q, const void *src);

void queue_dequeue(Queue *q, void *dest);



int main(){

  return 0;

}
