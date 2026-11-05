#ifndef STACK_H
#define STACK_H
#include <cstddef>
#include "List.h"
#include "Errors.h"
template<typename T>
class Stack {
    private:
        List<T> items;
    public:
        void push(const T& value);
        void pop(); 
        // mutable top value/ writeable
        T& top();
        //  immutuable/ only to read
        const T& top() const;
        bool empty() const;
        size_t getSize() const;
};

template<typename T> 
void Stack<T>::push(const T& value) {
    items.front_push(value);
}

template<typename T>
void Stack<T>::pop() {
    if (items.empty()) {
        throw EmptyStackError("pop on empty stack");
    }
    items.pop_front();
}

template<typename T> 
T& Stack<T>::top() {
    if (items.empty()) {
        throw EmptyStackError("top on empty stack");
    } 
    return items.front();
}

template<typename T> 
const T& Stack<T>::top() const {
    if (items.empty()) {
        throw EmptyStackError("top on empty stack");
    }
    return items.front();
}

template<typename T>
bool Stack<T>::empty() const {
    return items.empty();
}

template<typename T>
size_t Stack<T>::getSize() const {
    return items.getSize();
}
#endif