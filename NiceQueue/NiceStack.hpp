#include "NiceStack.h"

template <class T>
NiceStack<T>::NiceStack(size_t capacity) : storage(capacity), m_capacity(capacity), iHead(0)
{

}

template <class T>
NiceStack<T>::~NiceStack()
{
/* We don't need to do anything in destructor */
}

template <class T>
size_t NiceStack<T>::size() const
{
    return iHead;
}

template <class T>
void NiceStack<T>::push(T newelement) throw(std::out_of_range)
{
    // Check if the stack is full
    if (m_capacity == iHead)
        throw out_of_range("Stack overflow!");

    // Add new element
    if (iHead != 0)
        storage[iHead] = make_pair(newelement, min(newelement, storage[iHead - 1].second));
    else
        storage[iHead] = make_pair(newelement, newelement);

    // Increase number of elements in stack
    ++iHead;
}

template <class T>
T NiceStack<T>::pop() throw(std::out_of_range)
{
    // Check if the stack is empty
    if (iHead == 0)
        throw out_of_range("Stack is empty!");

    // Pop the element from the top
    return storage[--iHead].first;
}

template <class T>
T NiceStack<T>::getMinimum() throw (out_of_range)
{
    // Check if the stack is empty
    if (iHead == 0)
        throw out_of_range("Stack is empty!");

    // Return min
    return storage[iHead - 1].second;
}