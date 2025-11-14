#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

// i should mention i referenced this for clarity https://www.geeksforgeeks.org/dsa/introduction-to-circular-queue/

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ();
    explicit ABDQ(std::size_t capacity);
    ABDQ(const ABDQ& other);
    ABDQ(ABDQ&& other) noexcept;
    ABDQ& operator=(const ABDQ& other);
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ();

    // Insertion
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T& front() const override;
    const T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override;

    void PrintForward() const; //added myself
    void PrintReverse() const;
};

template <typename T>
ABDQ<T>::ABDQ() {
    capacity_ = 4;
    size_ = 0;
    front_ = 0;
    back_ = 0;
    data_ = new T[capacity_];
}

template <typename T>
ABDQ<T>::ABDQ(std::size_t capacity) {
    capacity_ = capacity;
    size_ = 0;
    front_ = 0;
    back_ = 0;
    data_ = new T[capacity_];
}

template <typename T>
ABDQ<T>::ABDQ(const ABDQ& other) {
       capacity_ = other.capacity_;
    size_ = other.size_;
    front_ = 0;
    back_ = size_;
    data_ = new T[capacity_];

    for (std::size_t i = 0; i < size_; ++i)
        data_[i] = other.data_[(other.front_ + i) % other.capacity_]; // i think?
}

template <typename T>
ABDQ<T>::ABDQ(ABDQ&& other) noexcept {
    data_ = other.data_;
    capacity_ = other.capacity_;
    size_ = other.size_;
    front_ = other.front_;
    back_ = other.back_;
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
    other.front_ = 0;
    other.back_ = 0;
}

template <typename T>
ABDQ<T>& ABDQ<T>::operator=(const ABDQ& rhs) {
    if (this == &rhs) {
        return *this; }

    delete[] data_;
    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    front_ = 0;
    back_ = size_;
    data_ = new T[capacity_];

    for (std::size_t i = 0; i < size_; ++i)
        data_[i] = rhs.data_[(rhs.front_ + i) % rhs.capacity_]; // i think?

    return *this;
}

template <typename T>
ABDQ<T>& ABDQ<T>::operator=(ABDQ&& rhs) noexcept {
    if (this == &rhs) return *this;

    delete[] data_;
    data_ = rhs.data_;
    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    front_ = rhs.front_;
    back_ = rhs.back_;

    rhs.data_ = nullptr;
    rhs.capacity_ = 0;
    rhs.size_ = 0;
    rhs.front_ = 0;
    rhs.back_ = 0;

    return *this;
}

template <typename T>
ABDQ<T>::~ABDQ() {
    delete[] data_;
}

//had to fix these 2
template <typename T>
void ABDQ<T>::pushFront(const T& item) {
    if (size_ >= capacity_) {
        std::size_t newCapacity = capacity_ * SCALE_FACTOR;
        T* newData = new T[newCapacity];

        for (std::size_t i = 0; i < size_; ++i)
            newData[i] = data_[(front_ + i) % capacity_];

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = size_;
    }

    front_ = (front_ + capacity_ - 1) % capacity_;
    data_[front_] = item;
    ++size_;
}

template <typename T>
void ABDQ<T>::pushBack(const T& item) {
    if (size_ >= capacity_) {
        std::size_t newCapacity = capacity_ * SCALE_FACTOR;
        T* newData = new T[newCapacity];

        for (std::size_t i = 0; i < size_; ++i)
            newData[i] = data_[(front_ + i) % capacity_];

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = size_;
    }

    data_[back_] = item;
    back_ = (back_ + 1) % capacity_;
    ++size_;
}

template <typename T>
T ABDQ<T>::popFront() {
    if (size_ == 0) throw std::runtime_error("deque empty");

    T val = data_[front_];
    front_ = (front_ + 1) % capacity_;
    --size_;

    // i made this to fix the sizing problem directly
    if (size_ <= capacity_ / 4 && capacity_ > 1) {
        std::size_t newCapacity = std::max(size_, std::size_t(1));
        newCapacity = capacity_ / 2; // shrink by half
        T* newData = new T[newCapacity];

        for (std::size_t i = 0; i < size_; ++i)
            newData[i] = data_[(front_ + i) % capacity_];

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = size_;
    }

    return val;
}

template <typename T>
T ABDQ<T>::popBack() {
    if (size_ == 0) throw std::runtime_error("deque empty");

    back_ = (back_ + capacity_ - 1) % capacity_;
    T val = data_[back_];
    --size_;

    // same thing
    if (size_ <= capacity_ / 4 && capacity_ > 1) {
        std::size_t newCapacity = std::max(size_, std::size_t(1));
        newCapacity = capacity_ / 2; // shrink by half
        T* newData = new T[newCapacity];

        for (std::size_t i = 0; i < size_; ++i)
            newData[i] = data_[(front_ + i) % capacity_];

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        front_ = 0;
        back_ = size_;
    }

    return val;
}



template <typename T>
const T& ABDQ<T>::front() const {
    if (size_ == 0) throw std::runtime_error("deque empty");
    return data_[front_];
}

template <typename T>
const T& ABDQ<T>::back() const {
    if (size_ == 0) throw std::runtime_error("deque empty");
    return data_[(back_ + capacity_ - 1) % capacity_];
}

template <typename T>
std::size_t ABDQ<T>::getSize() const noexcept {
    return size_;
}


//fixed these as well
template <typename T>
void ABDQ<T>::PrintForward() const {
    for (std::size_t i = 0; i < size_; ++i)
        std::cout << data_[(front_ + i) % capacity_] << "\n";
}
template <typename T>
void ABDQ<T>::PrintReverse() const {
    for (std::size_t i = 0; i < size_; ++i)
        std::cout << data_[(back_ + capacity_ - 1 - i) % capacity_] << "\n";
}