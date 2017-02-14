#include "NiceQueue.h"

template <class T>
NiceQueue<T>::NiceQueue(size_t capacity) : inStack(capacity), outStack(capacity), m_capacity(capacity)
{

}

template <class T>
size_t NiceQueue<T>::size() const
{
    return inStack.size() + outStack.size();
}

template <class T>
void NiceQueue<T>::enq(T newelement) throw (out_of_range)
{
    if (size() == m_capacity)
        throw out_of_range("Queue is full!");

    inStack.push(newelement);
}

template <class T>
T NiceQueue<T>::deq() throw (out_of_range)
{
    if (size() == 0)
        throw out_of_range("Queue is empty!");

    if (outStack.size() == 0 && inStack.size() > 0)
    {
        size_t k = inStack.size();
        for (int i = 0; i < k; ++i)
        {
            outStack.push(inStack.pop());
        }
    }
    return outStack.pop();
}

template <class T>
T NiceQueue<T>::getMinimum() throw (out_of_range)
{
    // Check if both stacks are empty
    if (size() == 0)
        throw out_of_range("Queue is empty!");

    // Check if both stacks are not empty
    if (inStack.size() > 0 && outStack.size() > 0)
        return min(inStack.getMinimum(), outStack.getMinimum());

    // Assuming only one stack is empty
    if (outStack.size() == 0)
        return inStack.getMinimum();
    else
        return outStack.getMinimum();
}