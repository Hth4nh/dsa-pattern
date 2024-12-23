#include <iostream>
#include <stdexcept>

template <typename T>
class Deque {
private:
    T* arr;
    size_t size, front, back;

public:
    Deque(int n) : size(n + 2), front(0), back(size - 1) {
        arr = new T[size];
    }

    ~Deque() {
        delete[] arr;
    }

    bool empty() const {
        return front == (back + 1) % size;
    }

    bool full() const {
        return front == (back + 2) % size;
    }

    void push_front(const T& value) {
        if (full()) throw std::overflow_error("Deque is full");
        front = (front - 1 + size) % size;
        arr[front] = value;
    }

    void push_back(const T& value) {
        if (full()) throw std::overflow_error("Deque is full");
        back = (back + 1) % size;
        arr[back] = value;
    }

    void pop_front() {
        if (empty()) throw std::underflow_error("Deque is empty");
        front = (front + 1) % size;
    }

    void pop_back() {
        if (empty()) throw std::underflow_error("Deque is empty");
        back = (back - 1 + size) % size;
    }

    T front() const {
        if (empty()) throw std::underflow_error("Deque is empty");
        return arr[front];
    }

    T back() const {
        if (empty()) throw std::underflow_error("Deque is empty");
        return arr[back];
    }

    size_t size() const {
        if (front <= back) {
            return back - front + 1;
        } else {
            return size - front + back + 1;
        }
    }

    size_t capacity() const {
        return size - 2;
    }

    T& operator[](size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return arr[(front + index) % size];
    }

    const T& operator[](size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return arr[(front + index) % size];
    }
};
