#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>
#include <iostream>


template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ();

    // Insertion
    void enqueue(const T& item) override;

    // Deletion
    T dequeue() override;

    // Access
    T peek() const override;

    // Getter
    std::size_t getSize() const noexcept override;

    void PrintForward() const; //added myself
    void PrintReverse() const;

};

template <typename T>
LLQ<T>::LLQ() {
}

template <typename T>
void LLQ<T>::enqueue(const T& item) {
    list.pushBack(item);
}

template <typename T>
T LLQ<T>::dequeue() {
    if (list.getSize() == 0) {
        throw std::runtime_error("queue empty"); //mentioned earlier in LLS but i used https://www.geeksforgeeks.org/cpp/how-to-throw-an-exception-in-cpp/
    }
    return list.popFront();
}

template <typename T>
T LLQ<T>::peek() const {
    if (list.getSize() == 0) {
        throw std::runtime_error("Queue empty"); //https://www.geeksforgeeks.org/cpp/how-to-throw-an-exception-in-cpp/
    }
    return list.getHead()->data;
}

template <typename T>
std::size_t LLQ<T>::getSize() const noexcept {
    return list.getSize();
}

template <typename T>
void LLQ<T>::PrintForward() const {
    list.PrintForward();
}

template <typename T>
void LLQ<T>::PrintReverse() const {
    list.PrintReverse();
}