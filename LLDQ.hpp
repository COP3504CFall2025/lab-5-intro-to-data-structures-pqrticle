#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ();

    // Core Insertion Operations
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Core Removal Operations
    T popFront() override;
    T popBack() override;

    // Element Accessors
    const T& front() const override;
    const T& back() const override;

    // Getter
    std::size_t getSize() const noexcept override;

    void PrintForward() const; //added myself
    void PrintReverse() const;
};

template <typename T>
LLDQ<T>::LLDQ() {
}

template <typename T>
void LLDQ<T>::pushFront(const T& item) {
    list.pushFront(item);
}

template <typename T>
void LLDQ<T>::pushBack(const T& item) {
    list.pushBack(item);
}

template <typename T>
T LLDQ<T>::popFront() {
    if (list.getSize() == 0) {
        throw std::out_of_range("Deque empty");
    }
    return list.popFront();
}

template <typename T>
T LLDQ<T>::popBack() {
    if (list.getSize() == 0) {
        throw std::out_of_range("Deque empty");
    }
    return list.popBack();
}

template <typename T>
const T& LLDQ<T>::front() const {
    if (list.getSize() == 0) {
        throw std::out_of_range("Deque empty");
    }
    return list.getHead()->data;
}

template <typename T>
const T& LLDQ<T>::back() const {
    if (list.getSize() == 0) {
        throw std::out_of_range("Deque empty");
    }
    return list.getTail()->data;
}

template <typename T>
std::size_t LLDQ<T>::getSize() const noexcept {
    return list.getSize();
}

template <typename T>
void LLDQ<T>::PrintForward() const {
    list.PrintForward();
}

template <typename T>
void LLDQ<T>::PrintReverse() const {
    list.PrintReverse();
}