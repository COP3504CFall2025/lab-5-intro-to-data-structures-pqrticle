#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <iostream>


// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS(); // done
    explicit ABS(const size_t capacity); //done
    ABS(const ABS& other); //done
    ABS& operator=(const ABS& rhs); //done
    ABS(ABS&& other) noexcept;//done
    ABS& operator=(ABS&& rhs) noexcept; //done
    ~ABS() noexcept; //done

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override; //done

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept; //done

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept; //done

    // Push item onto the stack
    void push(const T& data) override; //done

    T peek() const override; //done

    T pop() override; //done

    void PrintForward() const; //these arent shown for some reason
    void PrintReverse() const;

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};

template<typename T>
ABS<T>::ABS() {
    capacity_ = 1;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template<typename T>
ABS<T>::ABS(const size_t capacity) {
    capacity_ = capacity;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template<typename T>
ABS<T>::ABS(const ABS& other) {
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    array_ = new T[capacity_];
    for (size_t i = 0; i < curr_size_; ++i)
        array_[i] = other.array_[i];
}

template<typename T>
ABS<T>& ABS<T>::operator=(const ABS& rhs) {
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
ABS<T>::ABS(ABS&& other) noexcept {
    array_ = other.array_;
    capacity_ = other.capacity_;
    curr_size_ = other.curr_size_;
    other.array_ = nullptr;
    other.curr_size_ = 0;
    other.capacity_ = 0;
}

template<typename T>
ABS<T>& ABS<T>::operator=(ABS&& rhs) noexcept {
    if (this == &rhs)
        return *this;

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
ABS<T>::~ABS() noexcept {
    delete[] array_;
}

template<typename T>
void ABS<T>::push(const T& data) {
    if (curr_size_ >= capacity_) {

        capacity_ *= scale_factor_;
        T* new_array = new T[capacity_];
        for (size_t i = 0; i < curr_size_; ++i)
            new_array[i] = array_[i];
        delete[] array_;
        array_ = new_array;

}
array_[curr_size_++] = data;
}

template<typename T>
T ABS<T>::pop() {
    if (curr_size_ == 0)
        throw std::out_of_range("Stack is empty");
    --curr_size_;
    return array_[curr_size_];
}

template<typename T>
T ABS<T>::peek() const {
    if (curr_size_ == 0)
        throw std::out_of_range("Stack is empty");
    return array_[curr_size_ - 1];
}

template<typename T>
size_t ABS<T>::getSize() const noexcept {
    return curr_size_;
}

template<typename T>
size_t ABS<T>::getMaxCapacity() const noexcept {
    return capacity_;
}

template<typename T>
T* ABS<T>::getData() const noexcept {
    return array_;
}

template<typename T>
void ABS<T>::PrintForward() const {
    for (size_t i = 0; i < curr_size_; ++i)
        std::cout << array_[i] << "\n";
    std::cout << std::endl;
}

template<typename T>
void ABS<T>::PrintReverse() const {
    for (size_t i = curr_size_; i > 0; --i)
        std::cout << array_[i - 1] << "\n";
    std::cout << std::endl;
}