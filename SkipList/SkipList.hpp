/**
 * @author Nikita
 * @date 04.04.2017
 * Higher School of Economics,
 * Faculty of Computer Science,
 * Department of Software Engineering
 */


#include <cstdlib>

//=============================================================================
//== NodeSkipList =============================================================
//=============================================================================

template <class Value, class Key, int numLevels>
void NodeSkipList<Value,Key,numLevels>::clear(void)
{
	for (int i = 0; i < numLevels; ++i)
	{
		this->m_nextjump[i] = 0;
	}
	this->m_levelHighest = -1;
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(void)
{
	clear();
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key)
{
	clear();

	this->m_key = key;
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key, Value value)
{
	clear();

	this->m_key = key;
	this->m_value = value;
}
//=============================================================================
//== End of: NodeSkipList =====================================================
//=============================================================================

//=============================================================================
//== SkipList =================================================================
//=============================================================================
template <class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::SkipList(double probability)
{
	m_probability = probability;
	for (int i = 0; i < numLevels; ++i)
	{
		// Lets use m_pPreHead as a final sentinel element
		this->m_pPreHead->m_nextjump[i] = this->m_pPreHead;
	}
	this->m_pPreHead->m_levelHighest = numLevels-1;
}

template <class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::insert(Value value, Key key)
{
    TypeNode* current_node = this->m_pPreHead;

    // Array to store nodes (one from each level)
    // which keys were just smaller than the
    // key passed to the method
    TypeNode* smaller[this->m_pPreHead->m_levelHighest + 1];

    // Start descending from the top level
    int current_level = this->m_pPreHead->m_levelHighest;
    while(current_level >= 0)
    {
        // Moving to the next element on this level
        // while its value is smaller than our key
        // and it is not a prehead
        while((current_node->m_nextjump[current_level]->m_key < key)
              && (current_node->m_nextjump[current_level] != this->m_pPreHead))
            current_node = current_node->m_nextjump[current_level];

        // Remember the last smaller element
        smaller[current_level] = current_node;

        // Descend to the next level
        --current_level;
    }

    // Searching (on the base level) the node
    // after which we should insert the new one
    while((current_node->m_next->m_key <= key) && (current_node->m_next != this->m_pPreHead))
        current_node = current_node->m_next;

    // Create the node and insert it
    // in the appropriate place
    TypeNode* tbi = new TypeNode(key, value); // to be inserted
    tbi->m_next = current_node->m_next;
    current_node->m_next = tbi;

    // Start ascending from the bottom
    while (current_level < this->m_pPreHead->m_levelHighest)
    {
        // Toss the coin
        if (((double) rand() / (RAND_MAX)) > m_probability)
            // Stop when tail of the coin fell out
            break;

        // Insert the node in the next level of the list
        ++current_level;
        tbi->m_nextjump[current_level] = smaller[current_level]->m_nextjump[current_level];
        smaller[current_level]->m_nextjump[current_level] = tbi;
    }

    // Set the number of levels of the new node
    tbi->m_levelHighest = current_level;
}

template <class Value, class Key, int numLevels>
typename SkipList<Value, Key, numLevels>::TypeNode * SkipList<Value, Key, numLevels>::findFirst(Key key) const
{
    // Find the last node lass than the key
    TypeNode* lastLessThan = findLastLessThan(key);

    // Check if the next after the found
    // node's m_key equals to key
    if (lastLessThan->m_next->m_key == key && lastLessThan->m_next != this->m_pPreHead)
        // If so, then we have found the node
        // we were looking for
        return lastLessThan->m_next;

    // If not, then the node with
    // the defined key does not exists
    return nullptr;
}

template <class Value, class Key, int numLevels>
typename SkipList<Value, Key, numLevels>::TypeNode * SkipList<Value, Key, numLevels>::findLastLessThan(Key key) const
{

    // Check if the list if empty
    if (this->m_pPreHead->m_next == this->m_pPreHead)
        // If so, return the preHead
        return this->m_pPreHead;

    // Start descending from the top level
    // to find the node with such key
    TypeNode* current_node = this->m_pPreHead;
    int current_level = current_node->m_levelHighest;
    while (current_level >= 0)
    {
        // Continue to move to the next node on the current level
        // while the key of the current node is less than the key
        // we are looking for
        while(current_node->m_nextjump[current_level]->m_key < key
              && current_node->m_nextjump[current_level] != this->m_pPreHead)
            current_node = current_node->m_nextjump[current_level];

        // Descend to the next level of the list
        --current_level;
    }

    // Find the required node on the base level
    while(current_node->m_next->m_key < key && current_node->m_next != this->m_pPreHead)
        current_node = current_node->m_next;

    // If there is no node with the
    // defined key in the list
    return current_node;
}

template <class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::remove(TypeNode * node) {

    // Check if we are trying
    // to delete nullptr
    if (!node)
        throw std::invalid_argument("Can't delete nullptr");

    // Check if we are trying
    // to delete the prehead
    if (node == this->m_pPreHead)
        throw std::invalid_argument("Can't delete prehead");

    // Find the previous node on the base level
    TypeNode* previous_on_basement = this->m_pPreHead;
    while (previous_on_basement->m_next != this->m_pPreHead && previous_on_basement->m_next != node)
        previous_on_basement = previous_on_basement->m_next;

    // Check if the node is related to the list
    if (previous_on_basement->m_next != node)
        throw std::invalid_argument("Node does not exist in the list");

    // Start descending from the top level
    int current_level = node->m_levelHighest;
    while (current_level >= 0)
    {
        // Find the previous node on current level
        TypeNode* previous = this->m_pPreHead;
        while (previous->m_nextjump[current_level] != this->m_pPreHead && previous->m_nextjump[current_level] != node)
            previous = previous->m_nextjump[current_level];

        // Erase the node node on current level
        previous->m_nextjump[current_level] = node->m_nextjump[current_level];

        // Descend to the next level
        --current_level;
    }

    // Erase the node from the base level
    previous_on_basement->m_next = node->m_next;

    // Free the memory
    delete node;
}
//=============================================================================
//== End of: SkipList =========================================================
//=============================================================================
