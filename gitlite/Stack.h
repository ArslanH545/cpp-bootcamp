#ifndef STACK_H
#define STACK_H
#include "List.h"

template<typename T>
class Stack {
    private:
        List<T> stack;
    public:
        void push(const T& value);
        void pop(); 
};

template<typename T> 
void Stack<T>::push(const T& value) {
    stack.front_push(value);
}

template<typename T>
void Stack<T>::pop() {
    stack.pop_front();
}
#endif