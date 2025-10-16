#include "../include/circular_buffer_queuecpp.h"

// Définition des méthodes pour le template Queue<T>
template <typename T>
Queue<T>::Queue(size_t capacity) : front_(0), length_(0), capacity_(capacity) {
    data_ = new T[capacity_];
}

template <typename T>
Queue<T>::~Queue() {
    delete[] data_;
}

template <typename T>
bool Queue<T>::is_empty() const {
    return length_ == 0;
}

template <typename T>
size_t Queue<T>::size() const {
    return length_;
}

template <typename T>
void Queue<T>::enlarge_capacity() {
    size_t new_capacity = capacity_ * 2;
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < length_; i++) {
        size_t index = (front_ + i) % capacity_;
        new_data[i] = data_[index];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
    front_ = 0;
}

template <typename T>
void Queue<T>::enqueue(const T& item) {
    if (length_ == capacity_) enlarge_capacity();
    size_t rear = (front_ + length_) % capacity_;
    data_[rear] = item;
    length_++;
}

template <typename T>
T Queue<T>::dequeue() {
    if (is_empty()) throw std::runtime_error("Queue vide");
    T item = data_[front_];
    front_ = (front_ + 1) % capacity_;
    length_--;
    return item;
}

template class Queue<int>; // instanciation explicite
