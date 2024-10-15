#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <typename T>
Queue<T>::Queue(size_t capacity) {
	data = (T*)malloc(capacity * sizeof(T));
	front = 0;
	length = 0;
	this->capacity = capacity;
}

template <typename T>
bool Queue<T>::is_empty() {
	return (length) == 0;
}

template <typename T>
size_t Queue<T>::get_length() {
	return length;
}

template <typename T>
void Queue<T>::dispose() {
	free(data);
}

// Push the src to the back of the tail
template <typename T>
void Queue<T>::enqueue(T val) {
	if (length >= capacity) {
		size_t old_capacity = capacity;
		enlarge_capacity();
		// Copy elements before head to after head since capacity was
		// added.
		for (int i = 0; i < front; i++) {
			data[old_capacity + i] = data[i];
		}
	}
	// Enqueue the element.
	size_t tail = (front + length) % capacity;
	data[tail] = val;
	length++;
	return;
}

// Pull the head element to dest
template <typename T>
T Queue<T>::dequeue() {
	if (is_empty()) {
		return NULL;
	} else {
		T return_val = data[front];
		front = (front + 1) % capacity;
		length--;
		return return_val;
	}
}

template <typename T>
void Queue<T>::enlarge_capacity() {
	data = (T*)realloc(data, (capacity * 2) * sizeof(T));
	capacity = capacity * 2;
}

template <typename T>
void Queue<T>::print_queue() {
	for (int i = 0; i < capacity; i++) {
		int* elem = (T*)(data) + i;
		printf("%d\n", *elem);
	}
}

