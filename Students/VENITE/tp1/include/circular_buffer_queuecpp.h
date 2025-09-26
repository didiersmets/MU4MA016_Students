#include <cstddef>
#include <stdexcept>

// Template pour queue générique
template <typename T>
class Queue {
private:
    size_t front_;
    size_t length_;
    size_t capacity_;
    T* data_;

    void enlarge_capacity();

public:
    Queue(size_t capacity);
    ~Queue();

    bool is_empty() const;
    size_t size() const;

    void enqueue(const T& item);
    T dequeue();
};


