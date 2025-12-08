#ifndef CIRCULAR_BUFFER_QUEUE_H
#define CIRCULAR_BUFFER_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

// question 1 Circular buffers (1)
struct Queue {
    size_t front;     // 队首元素下标
    size_t length;    // 当前元素个数
    size_t capacity;  // 最大可容纳元素个数
    size_t elem_size; // 每个元素的字节数
    void *data;       // 底层数组
};

// 初始化；返回堆上分配的队列指针
struct Queue *queue_init(size_t elem_size, size_t capacity);

// 销毁
void queue_free(struct Queue *q);

// 入队：把 *src 的 elem_size 字节拷入队尾
void queue_enqueue(struct Queue *q, const void *src);

// 出队：把队首元素拷贝到 *dest
bool queue_dequeue(struct Queue *q, void *dest);

// 查询
static inline bool queue_empty(const struct Queue *q){ return q->length == 0; }
static inline size_t queue_size(const struct Queue *q){ return q->length; }

#endif
