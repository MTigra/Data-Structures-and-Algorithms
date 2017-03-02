///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains pseudo-implementation part of bidirectional list structure 
/// template declared in the file's h-counterpart
///
/// © Sergey Shershakov 2015–2016
///
/// No part of this code can be used without an explicit permission of the author.
/// The exception is done for educational goals of the course "Algorithms and Data
/// Structures" provided by the School of Software Engineering of the Faculty
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////

#include <stdexcept>
#include "BidiLinkedList.h"

//==============================================================================
// class BidiList<T>::Node
//==============================================================================


template <typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::Node::insertAfterInternal(Node* insNode)
{
    // Here we use "this" keyword for enhancing the fact we deal with current node!
    Node* afterNode = this->_next;      // An element, which was after node

    this->_next = insNode;
    insNode->_prev = this;

    // Check that it is not the last node
    if (afterNode)
    {
        // Set the pointers respectively
        insNode->_next = afterNode;
        afterNode->_prev = insNode;
    }

    // Return the inserted node
    return insNode;
}

//==============================================================================
// class BidiList<T>
//==============================================================================

template <typename T>
BidiLinkedList<T>::~BidiLinkedList()
{
    clear();
}


template <typename T>
void BidiLinkedList<T>::clear()
{
    Node* current_node = _head; // Iteration node

    // Iterate to the end of the
    // list deleting its elements
    while (current_node)
    {
        Node* tbd_node = current_node; // Node to be deleted
        current_node = current_node->_next;
        delete tbd_node;
    }
    _head = nullptr;

    // Invalidate size
    invalidateSize();
}


template <typename T>
size_t BidiLinkedList<T>::getSize()
{
    if (_size == NO_SIZE)
        calculateSize();

    return _size;
}


template <typename T>
void BidiLinkedList<T>::calculateSize()
{
    // Create a node to iterate through the list
    Node* current_node = _head;

    // Reset size value
    _size = 0;

    // Calculate size by passing
    // to the end of the list
    while (current_node)
    {
        ++_size;
        current_node = current_node->_next;
    }
}


template <typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::getLastNode() const
{
    // Iterate to the end of the list
    Node* current_node = _head;
    while (current_node && current_node->_next)
        current_node = current_node->_next;

    // Return the last node
    return current_node;
}


template <typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::appendEl(const T& val)
{
    Node* newNode = new Node(val);

    // inserts after last node, size is going to be invalidated there
    return insertNodeAfter(getLastNode(), newNode);
}


template <typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::insertNodeAfter(Node* node, Node* insNode)
{
    // Check if insNode is nullptr
    if (!insNode)
        throw std::invalid_argument("`insNode` is nullptr");

    if (!node)
        node = getLastNode();

    // If last node is nullptr it means that the list is empty
    if (!node)
        _head = insNode;
    else
        node->insertAfterInternal(insNode);

    // Invalidate size
    invalidateSize();

    return insNode;
}


template <typename T>
void BidiLinkedList<T>::insertNodesAfter(Node* node, Node* beg, Node* end)
{
    // Check if the begin/end is nullptr
    if (!beg || !end)
        throw std::invalid_argument("Either `beg` or `end` is nullptr");

    if (!node)
        node = getLastNode();

    // If last node is nullptr it means that the list is empty
    if (!node)
    {
        _head = beg;
        return;
    }

    // Insert the chain
    Node* last_node = node->_next; // Remember the node which should go after 'end'
    node->_next = beg;
    beg->_prev = node;

    // Check if the node was the last element
    // and its _next field is nullptr
    end->_next = last_node;
    if (last_node)
        last_node->_prev = end;

    invalidateSize();
}

#ifdef IWANNAGET10POINTS

template <typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::insertNodeBefore(Node* node, Node* insNode)
{
    // Check if insNode is nullptr
    if (!insNode)
        throw std::invalid_argument("`insNode` is nullptr");

    if (!node)
        node = _head;

    // If last node is nullptr it means that the list is empty
    if (!node)
        _head = insNode;
    else if (!node->_prev) // Insert before head
    {
        insNode->_next = _head;
        _head->_prev = insNode;
        _head = insNode;
        _head->_prev = nullptr;
    }
    else // Insert between 2 nodes
        node->_prev->insertAfterInternal(insNode);

    // Invalidate size
    invalidateSize();

    return insNode;
}


template <typename T>
void BidiLinkedList<T>::insertNodesBefore(Node* node, Node* beg, Node* end)
{
    // Check if the begin/end is nullptr
    if (!beg || !end)
        throw std::invalid_argument("Either `beg` or `end` is nullptr");

    if (!node)
        node = _head;

    // If last node is nullptr it means that the list is empty
    if (!node)
    {
        _head = beg;
        return;
    }
    else if (!node->_prev) // Insert before head
    {
        _head->_prev = end;
        end->_next = _head;
        _head = beg;
        _head->_prev = nullptr;
    }
    else // Insert between 2 nodes
    {
        Node* tmp_node = node->_prev;
        node->_prev = end;
        end->_next = node;
        tmp_node->_next = beg;
        beg->_prev = tmp_node;
    }

    // Invalidate size
    invalidateSize();
}

#endif // IWANNAGET10POINTS


template <typename T>
void BidiLinkedList<T>::cutNodes(Node* beg, Node* end)
{
    // Check for nullptr
    if (!beg || !end)
        throw std::invalid_argument("Either `beg` or `end` is nullptr");

    if (!beg->_prev && !end->_next) // All nodes
        _head = nullptr;
    else if (!beg->_prev && end->_next)
    {
        _head = end->_next;
        _head->_prev = nullptr;
    }
    else if (beg->_prev && !end->_next)
        beg->_prev->_next = nullptr;
    else
    {
        beg->_prev->_next = end->_next;
        end->_next->_prev = beg->_prev;
    }

    // Invalidate size
    invalidateSize();
}


template <typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::cutNode(Node* node)
{
    // Check if the node is nullptr
    if (!node)
        throw std::invalid_argument("Can't cut nullptr node!");

    if (!node->_prev) // It is head
    {
        _head = node->_next;
        _head->_prev = nullptr;
    }
    else if (!node->_next) // It is end
        node->_prev->_next = nullptr;
    else // It is in between 2 nodes
    {
        node->_prev->_next = node->_next;
        node->_next->_prev = node->_prev;
    }

    // Invalidate size
    invalidateSize();

    return node;
}


template <typename T>
typename BidiLinkedList<T>::Node*
BidiLinkedList<T>::findFirst(Node* startFrom, const T& val)
{
    // Check if starting Node is nullptr
    if (!startFrom)
        return nullptr;

    // Iterate through the list till the
    // required element is found
    while (startFrom)
    {
        if (startFrom->_val == val)
            return startFrom;
        startFrom = startFrom->_next;
    }

    // Not found
    return nullptr;
}


template <typename T>
typename BidiLinkedList<T>::Node**
BidiLinkedList<T>::findAll(Node* startFrom, const T& val, int& size)
{
    if (!startFrom)
        return nullptr;


    Node** res = nullptr;
    size = 0;

    while (startFrom)
    {
        if (startFrom->_val == val) {
            if (!res) // Array is not initialized
                res = new Node*[getSize()];

            // Add matched node to the array of results
            res[size] = startFrom;

            // Increment size
            ++size;
        }

        // Get next node
        startFrom = startFrom->_next;
    }

    // Crop array if the matched items found
    if (res)
    {
        Node** new_res = new Node*[size];

        // Copy elements
        for (int i = 0; i < size; ++i)
            new_res[i] = res[i];

        // Delete an old array
        delete[] res;

        res = new_res;
    }

    // Return all matched nodes
    return res;
}

#ifdef IWANNAGET10POINTS

template <typename T>
typename BidiLinkedList<T>::Node**
BidiLinkedList<T>::cutAll(Node* startFrom, const T& val, int& size)
{
    if (!startFrom)
        return nullptr;

    // Find all nodes in the list with matching val
    // and store them into the array
    Node** res = findAll(startFrom, val, size);

    // Cut these nodes from the list
    for (int i = 0; i < size; ++i)
        cutNode(res[i]);

    // Return all non-matching nodes
    return res;
}

#endif // IWANNAGET10POINTS