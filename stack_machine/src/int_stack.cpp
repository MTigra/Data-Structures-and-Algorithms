////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Sergey Shershakov, Nikita Marinosyan
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "int_stack.h"

#include <stdexcept>

using namespace std;

namespace xi {

    IntStack::IntStack(size_t sz) {

        _stack = new int[sz];
        _ssize = sz;
        _head = 0;
    }

    IntStack::~IntStack() {

        delete[] _stack;
        _stack = nullptr;
        _ssize = 0;
        _head = 0;
    }

    void IntStack::clear() {
        _head = 0;
    }

    bool IntStack::isFull() const {
        return _ssize == _head;
    }

    bool IntStack::isEmpty() const {
        return _head == 0;
    }

    void IntStack::push(int el) {
        if (isFull()) throw logic_error("Stack overflow!");
        _stack[_head++] = el;
    }

    int IntStack::pop() {
        if (isEmpty()) throw logic_error("Stack is empty!");
        return _stack[--_head];
    }

    int IntStack::top() {
        if (isEmpty()) throw logic_error("Stack is empty!");
        return _stack[_head - 1];
    }

} // namespace xi