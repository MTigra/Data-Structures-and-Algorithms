////////////////////////////////////////////////////////////////////////////////
// Module Name:  linked_list.h/cpp
// Authors:      Nikita Marinosyan, Sergey Shershakov, Leonid Dworzanski
// Date:         06.02.2017
// Copyright (c) The Team of "Algorithms and Data Structures" 2014–2017.
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
//
// Отделенная часть заголовка шаблона класса "Связанный список"
//
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>
#include "linked_list.h"

namespace xi {

template <class T>
LinkedList<T>::LinkedList() 
{
    // Creation of the dummy/sentinel element
    _preHead = new Node<T>;
    _preHead->next = nullptr;
}

template <class T> 
LinkedList<T>::~LinkedList()
{
    while  (_preHead->next)
        deleteNextNode(_preHead);

    delete _preHead;
}

template <class T>
void LinkedList<T>::copy(Node <T>* from_preHead, Node <T>* to_preHead)
{
    Node<T>* from_iter = from_preHead;
    Node<T>* to_iter = to_preHead;
    while (from_iter)
    {
        // Create new node
        Node<T>* new_node = new Node<T>;
        new_node->value = from_iter->value;
        to_iter->next = new_node;

        // Next step
        to_iter = to_iter->next;
        from_iter = from_iter->next;
    }
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList& other)
{
    copy(other._preHead, _preHead);
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList <T>& other)
{
    if (this != &other)
    { // Self-assignment check

        // Delete this list nodes
        while  (_preHead->next)
            deleteNextNode(_preHead);

        // Copy the list
        copy(other._preHead, _preHead);
    }

    return *this;
}

template <class T>
int LinkedList<T>::size()
{
    // Variable for counting the number of elements
    int size = 0;

    // Pointer to the current node
    Node<T>* current_node = _preHead->next;

    while (current_node)
    { // While there is a node
        ++size; // Increment the size
        current_node = current_node->next; // Set the pointer to the next node
    }

    return size;
}

template <class T>
Node<T>* LinkedList<T>::getPreHead()
{
    return _preHead;
}

template <class T>
T& LinkedList<T>::operator[](int i)
{

    Node<T>* current_node = _preHead->next;
    for (int j = 0; j < i; ++j)
    {
        current_node = current_node->next;
    }

    if (!current_node)
        throw std::out_of_range("Index out of bounds!");

    return current_node->value;
}

template <class T>
void LinkedList<T>::addElementToEnd(T& value)
{
    // Create new node and add it to the end
    Node<T>* new_node = new Node<T>;
    new_node->value = value;
    getLastNode()->next = new_node;
}

template <class T>
void LinkedList<T>::deleteNextNode(Node <T>* pNodeBefore)
{
    Node<T>* tmp_node = pNodeBefore->next->next;
    delete pNodeBefore->next;
    pNodeBefore->next = tmp_node;
}

template <class T>
void LinkedList<T>::deleteNodes(Node <T>* pNodeBefore, Node <T>* pNodeLast)
{
    while(pNodeBefore->next != pNodeLast)
    {
        deleteNextNode(pNodeBefore);
    }

    // Delete the last one
    deleteNextNode(pNodeBefore);
}

template <class T>
void LinkedList<T>::moveNodeAfter(Node <T>* pNode, Node <T>* pNodeBefore)
{
    // Make the required re-links
    Node<T>* tmp_node = pNodeBefore->next;
    pNodeBefore->next = tmp_node->next;
    tmp_node->next = pNode->next;
    pNode->next = tmp_node;
}

template <class T>
void LinkedList<T>::moveNodesAfter(Node <T>* pNode, Node <T>* pNodeBefore, Node <T>* pNodeLast)
{
    Node<T>* current_node = pNodeBefore;
    Node<T>* current_other = pNode;
    while (current_node->next != pNodeLast)
    {
        moveNodeAfter(current_other, current_node);
        current_other = current_other->next;
        current_node = current_node->next;
    }

    // Move the last one
    moveNodeAfter(current_other, current_node);
}

template <class T>
Node<T>* LinkedList<T>::getLastNode()
{
    // Get the last node
    Node<T>* last_node = _preHead;
    while(last_node)
        last_node = last_node->next;

    return last_node;
}

template <class T>
void LinkedList<T>::moveNodeToEnd(Node <T>* pNodeBefore)
{
    // Get the last node
    Node<T>* last_node = getLastNode();

    moveNodeAfter(last_node, pNodeBefore->next);
}

template <class T>
void LinkedList<T>::moveNodesToEnd(Node <T>* pNodeBefore, Node <T>* pNodeLast)
{
    Node<T>* current_node = pNodeBefore;
    while (current_node->next != pNodeLast)
    {
        moveNodeToEnd(current_node);
        current_node = current_node->next;
    }

    // Move the last one
    moveNodeToEnd(current_node);
}


} // namespace xi