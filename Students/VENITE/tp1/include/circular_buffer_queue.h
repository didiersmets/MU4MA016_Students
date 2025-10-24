#include <stddef.h> // Provides size_t
#include <stdbool.h> // Provides the bool type and true/false

struct Queue {
    size_t front;
    size_t length;
    size_t capacity;
    size_t elem_size;
    void *data;
};

struct Queue *queue_init(size_t elem_size, size_t capacity);

void queue_destroy(struct Queue *q);

void queue_enqueue(struct Queue *q, const void *src);

void queue_dequeue(struct Queue *q, void *dest);

bool queue_is_empty(const struct Queue *q);




