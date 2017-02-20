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
    // here we use "this" keyword for enhancing the fact we deal with current node!
    Node* afterNode = this->_next;      // an element, which was after node

    // Insert insNode
    this->_next = insNode;

    // Set the pointers respectively
    insNode->_next = afterNode;
    insNode->_prev = this;

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
    Node<T>* current_node = _head->_next; // Iteration node
    Node<T>* tbd_node; // Node to be deleted //TODO do i need to write Node<T>* or it can be just Node* ?

    // Iterate to the end of the
    // list deleting its elements
    while (current_node)
    { //TODO easier?
        tbd_node = current_node;
        current_node = current_node->_next;
        delete tbd_node;
    }

    // Delete the last (head) node
    // if it is not nullptr
    if (_head)
        delete _head;

    // Invalidate size
    invalidateSize(); //TODO do i need to do this?
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
    Node<T>* current_node = _head;

    // Reset size value
    _size = 0;

    // Calculate size by passing
    // to the end of the list
    while (current_node)
    {
        ++_head;
        current_node = current_node->_next;
    }
}


template <typename T>
typename BidiLinkedList<T>::Node* 
    BidiLinkedList<T>::getLastNode() const
{
    // Iterate to the end of the list
    Node<T>* current_node = _head;
    while (current_node)
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
    Node<T>* last_node = node->_next; // Remember the node which should go after 'end'
    node->_next = beg;
    beg->_prev = node;
    end->_next = last_node;
    last_node->_prev = end;

    invalidateSize();
}

// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS


template <typename T>
typename BidiLinkedList<T>::Node*
    BidiLinkedList<T>::insertNodeBefore(Node* node, Node* insNode)
{



    // !...
    // Реализуй метод, если хочешь получит оценку повыше!
    // !...



}


template <typename T>
void BidiLinkedList<T>::insertNodesBefore(Node* node, Node* beg, Node* end)
{
    // !...
    // Реализуй метод, если хочешь получит оценку повыше!
    // !...

}



#endif // IWANNAGET10POINTS


template <typename T>
void BidiLinkedList<T>::cutNodes(Node* beg, Node* end)
{
    // Check for nullptr
    if (!beg || !end)
        throw std::invalid_argument("Either `beg` or `end` is nullptr");

    // Rearrange pointers
    beg->_prev->_next = end->_next;
    end->_next->_prev = beg->_prev;

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

    // Rearrange pointers
    node->_prev->_next = node->_next;
    node->_next->_prev = node->_prev;

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
        if (startFrom->_val = val)
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

    while (startFrom) //TODO do i do it right?
    {
        if (startFrom->_val == val) { // Array is not initialized
            if (!res)
                res = new Node<T>*[1];
            else
            {   // Array is initialized
                Node<T>** res_new = new Node<T>*[size + 1];
                delete[] res;
                res = res_new;
            }

            // Increment size
            ++size;
        }

        // Get next node
        startFrom = startFrom->_next;
    }

    // Return all matched nodes
    return res;
}

// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS

template <typename T>
typename BidiLinkedList<T>::Node**  
BidiLinkedList<T>::cutAll(Node* startFrom, const T& val, int& size)
{

    // !...
    // Реализуй метод, если хочешь получит оценку повыше!
    // !...


}

#endif // IWANNAGET10POINTS