#include <stdbool.h>
#include <stddef.h>  // for size_t

template <typename T>
class Queue {
       public:
	size_t front;	  // index of the first element in the queue
	size_t length;	  // number of items presently in the queue
	size_t capacity;  // capacity of the queue (in nbr of items)
	T *data;	  // address of the array
	Queue(size_t capacity);
	bool is_empty();
	size_t get_length();
	void dispose();
	void enqueue(T val);
	T dequeue();
	void enlarge_capacity();
	void print_queue();
};

#include "circular_buffer_queue.inl"
