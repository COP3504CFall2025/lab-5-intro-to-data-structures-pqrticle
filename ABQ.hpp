#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <iostream>


// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ(); //done
    explicit ABQ(const size_t capacity); //done
    ABQ(const ABQ& other); //done
    ABQ& operator=(const ABQ& rhs); //done
    ABQ(ABQ&& other) noexcept; //done
    ABQ& operator=(ABQ&& rhs) noexcept; //done
    ~ABQ() noexcept; //done

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override; //done
    [[nodiscard]] size_t getMaxCapacity() const noexcept; //done
    [[nodiscard]] T* getData() const noexcept; //done

    // Insertion
    void enqueue(const T& data) override; //done

    // Access
    T peek() const override;//done

    // Deletion
    T dequeue() override;//done

    void PrintForward() const; // same issue where these arent shown
    void PrintReverse() const;

};

template<typename T>
ABQ<T>::ABQ() {
    capacity_ = 1;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template<typename T>
ABQ<T>::ABQ(const size_t capacity) {
    capacity_ = capacity;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template<typename T>
ABQ<T>::ABQ(const ABQ& other) {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = new T[capacity_];
    for (size_t i = 0; i < curr_size_; ++i)
        array_[i] = other.array_[i];
}

template<typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ& rhs) {
    if (this == &rhs)
        return *this;

    delete[] array_;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = new T[capacity_];
    for (size_t i = 0; i < curr_size_; ++i)
        array_[i] = rhs.array_[i];

    return *this;
}

template<typename T>
ABQ<T>::ABQ(ABQ&& other) noexcept {
    array_ = other.array_;
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    other.array_ = nullptr;
    other.curr_size_ = 0;
    other.capacity_ = 0;
}

template<typename T>
ABQ<T>& ABQ<T>::operator=(ABQ&& rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }

    delete[] array_;
    array_ = rhs.array_;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    rhs.array_ = nullptr;
    rhs.curr_size_ = 0;
    rhs.capacity_ = 0;
    
    return *this;
}

template<typename T>
ABQ<T>::~ABQ() noexcept {
    delete[] array_;
}

template<typename T>
void ABQ<T>::enqueue(const T& data) {

    if (curr_size_ >= capacity_) {
        size_t new_capacity = capacity_ * scale_factor_;
        T* new_array = new T[new_capacity];
        for (size_t i = 0; i < curr_size_; ++i)
            new_array[i] = array_[i];
        delete[] array_;
        array_ = new_array;
        capacity_ = new_capacity;
    }

    array_[curr_size_++] = data;
}

template<typename T>
T ABQ<T>::dequeue() {
    if (curr_size_ == 0)
        throw std::out_of_range("Queue is empty");

    T result = array_[0];

    // shift elements left
    for (size_t i = 1; i < curr_size_; ++i)
        array_[i - 1] = array_[i];

    --curr_size_;
    return result;
}

template<typename T>
T ABQ<T>::peek() const {
    if (curr_size_ == 0)
        throw std::out_of_range("Queue is empty");
    return array_[0];
}

template<typename T>
size_t ABQ<T>::getSize() const noexcept {
    return curr_size_;
}

template<typename T>
size_t ABQ<T>::getMaxCapacity() const noexcept {
    return capacity_;
}

template<typename T>
T* ABQ<T>::getData() const noexcept {
    return array_;
}

template<typename T>
void ABQ<T>::PrintForward() const {
    for (size_t i = 0; i < curr_size_; ++i)
        std::cout << array_[i] << "\n";
    std::cout << std::endl;
}

template<typename T>
void ABQ<T>::PrintReverse() const {
    for (size_t i = curr_size_; i > 0; --i)
        std::cout << array_[i - 1] << "\n";
    std::cout << std::endl;
}