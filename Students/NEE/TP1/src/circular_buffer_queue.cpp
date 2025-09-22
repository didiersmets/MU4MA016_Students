#include <stdexcept>
#include <iostream>

template <typename T>
class Queue
{
private:
    size_t front;
    size_t length;
    size_t capacity;
    T *data;

public:
    explicit Queue(size_t capacity);
    ~Queue();
    void enqueue(const T &item);
    T dequeue();
    bool is_empty() const;
    size_t size() const;

private:
    void enlarge_capacity();
};

template <typename T>
Queue<T>::Queue(size_t initial_capacity)
    : front(0), length(0), capacity(initial_capacity)
{
    data = new T[capacity];
}

template <typename T>
Queue<T>::~Queue()
{
    delete[] data;
}

template <typename T>
bool Queue<T>::is_empty() const
{
    return length == 0;
};
template <typename T>
size_t Queue<T>::size() const
{
    return length;
};

template <typename T>
void Queue<T>::enqueue(const T &item)
{
    if (length >= capacity)
    { // Changed from < to >=
        enlarge_capacity();
    }
    data[(front + length) % capacity] = item; // Fixed parentheses
    length++;
}

template <typename T>
T Queue<T>::dequeue()
{
    if (is_empty())
    {
        throw std::runtime_error("Queue is empty");
    }

    T result = data[front];
    front = (front + 1) % capacity;
    length--;
    return result;
}

template <typename T>
void Queue<T>::enlarge_capacity()
{
    size_t new_capacity = capacity * 2;
    T *new_data = new T[new_capacity];
    // Copy elements in order from old circular buffer to new linear buffer
    for (size_t i = 0; i < length; i++)
    {
        new_data[i] = data[(front + i) % capacity]; // Direct assignment!
    }
    delete[] data;
    data = new_data;
    front = 0; // Reset front since new buffer is linear
    capacity = new_capacity;
}

int main()
{
    Queue<int> q(2); // Start with tiny capacity

    std::cout << "Adding elements beyond initial capacity..." << std::endl;

    for (int i = 1; i <= 5; i++)
    {
        q.enqueue(i * 10);
        std::cout << "Enqueued " << i * 10 << ", Size: " << q.size() << std::endl;
    }

    std::cout << "\nDequeuing all elements:" << std::endl;
    while (!q.is_empty())
    {
        std::cout << "Dequeued: " << q.dequeue() << std::endl;
    }

    return 0;
}