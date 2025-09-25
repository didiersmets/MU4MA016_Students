#include <stdbool.h>
#include <stddef.h> // for size_t

template<typename T>
struct Queue {
	size_t front; // index of the first element in the queue
	size_t length; // number of items presently in the queue
	size_t capacity; // capacity of the queue (in nbr of items)
	T *data; // address of the array
};

template<typename T>
bool is_empty(const Queue<T> *q);

template<typename T>
size_t queue_length(const Queue<T> *q);

template<typename T>
struct Queue<T> *queue_init(size_t capacity);

template<typename T>
void queue_dispose(Queue<T> *q);

template<typename T>
void queue_enqueue(Queue<T> *q, const void *src);

template<typename T>
void queue_dequeue(Queue<T> *q, void *dest);


// Implementation
#include <stdlib.h>
#include <string.h>

template<typename T>
static void enlarge_queue_capacity(Queue<T> *q);

template<typename T>
bool is_empty(const Queue<T> *q) {
    return queue_length(q) == 0;
}

template<typename T>
size_t queue_length(const Queue<T> *q) {
    return q->length;
}

template<typename T>
struct Queue<T> *queue_init(size_t capacity) {
    if(capacity == 0) {
        return NULL; // Capacity must be greater than 0
    }
    T* data = (T*) malloc(sizeof(T) * capacity);
    if (data == NULL) {
        return NULL; // Memory allocation failed
    }
    Queue<T>* q = (Queue<T>*) malloc(sizeof(Queue<T>));
    if (q == NULL) {
        return NULL;
    }
    q->front = 0;
    q->length = 0;
    q->capacity = capacity;
    q->data = data;
    return q;
}

template<typename T>
void queue_dispose(Queue<T> *q) {
    free(q->data);
    free(q);
}

template<typename T>
void queue_enqueue(Queue<T> *q, const T*src) {
    if (q->length == q->capacity) {
        enlarge_queue_capacity(q);
    }
    size_t insert_index = (q->front + q->length) % q->capacity;
    q->data[insert_index] = *src;
    q->length++;
}

template<typename T>
void queue_dequeue(Queue<T> *q, T *dest) {
    if (is_empty(q)) {
        dest = NULL;
        return; // Queue is empty
    }
    *dest = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->length--;
}

template<typename T>
static void enlarge_queue_capacity(Queue<T> *q) {
    q->data = (T*) realloc(q->data, sizeof(T) * q->capacity * 2);

    // copy looping data
    for(size_t i = q->capacity; i < q->front + q->length; i++) {
        size_t from_index = i - q->capacity;
        size_t to_index = i;
        q->data[i] = q->data[from_index];
    }

    q->capacity *= 2;
}