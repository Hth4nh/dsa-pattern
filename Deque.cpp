#include <iostream>
#include <stdexcept>

template <typename T>
class Deque {
private:
    T* arr;
    size_t n, start, end;

public:
    Deque(int size) : n(size + 2), start(0), end(n - 1) {
        arr = new T[n];
    }

    ~Deque() {
        delete[] arr;
    }

    bool empty() const {
        return start == (end + 1) % n;
    }

    bool full() const {
        return start == (end + 2) % n;
    }

    void push_front(const T& value) {
        if (full()) throw std::overflow_error("Deque is full");
        start = (start - 1 + n) % n;
        arr[start] = value;
    }

    void push_back(const T& value) {
        if (full()) throw std::overflow_error("Deque is full");
        end = (end + 1) % n;
        arr[end] = value;
    }

    void pop_front() {
        if (empty()) throw std::underflow_error("Deque is empty");
        start = (start + 1) % n;
    }

    void pop_back() {
        if (empty()) throw std::underflow_error("Deque is empty");
        end = (end - 1 + n) % n;
    }

    T front() const {
        if (empty()) throw std::underflow_error("Deque is empty");
        return arr[start];
    }

    T back() const {
        if (empty()) throw std::underflow_error("Deque is empty");
        return arr[end];
    }

    size_t size() const {
        if (start <= end) {
            return end - start + 1;
        } else {
            return n - start + end + 1;
        }
    }

    size_t capacity() const {
        return n - 2;
    }

    void clear() {
        start = 0;
        end = n - 1;
    }

    T& operator[](size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return arr[(start + index) % n];
    }

    const T& operator[](size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return arr[(start + index) % n];
    }
};
