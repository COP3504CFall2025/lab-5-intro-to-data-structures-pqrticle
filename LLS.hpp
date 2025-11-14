#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS();

    // Insertion
    void push(const T& item) override;

    // Deletion
    T pop() override;

    // Access
    T peek() const override;

    //Getters
    std::size_t getSize() const noexcept override;

    void PrintForward() const; //added myself
    void PrintReverse() const;
};

template<typename T>
void LLS<T>::push(const T& item) {
    list.pushFront(item);
}

template<typename T>
T LLS<T>::pop() {
    if (list.getSize() == 0)
        throw std::out_of_range("stack empty"); //had to look this up https://www.geeksforgeeks.org/cpp/how-to-throw-an-exception-in-cpp/
    return list.popFront();
}

template<typename T>
T LLS<T>::peek() const {
    if (list.getSize() == 0)
        throw std::out_of_range("stack empty"); // https://www.geeksforgeeks.org/cpp/how-to-throw-an-exception-in-cpp/
    return list.getHead()->data;
}

template<typename T>
std::size_t LLS<T>::getSize() const noexcept {
    return list.getSize();
}

template<typename T>
void LLS<T>::PrintForward() const {
    list.PrintForward();
}

template<typename T>
void LLS<T>::PrintReverse() const {
    list.PrintReverse();
}