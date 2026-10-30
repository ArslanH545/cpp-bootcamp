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
        bool empty();
        
};


#endif