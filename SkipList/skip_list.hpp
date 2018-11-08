////////////////////////////////////////////////////////////////////////////////
// Module Name:  skip_list.h/hpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      2.0.0
// Date:         28.10.2018
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

// !!! DO NOT include skip_list.h here, 'cause it leads to circular refs. !!!

#include <cstdlib>

//==============================================================================
// class NodeSkipList
//==============================================================================

template <class Value, class Key, int numLevels>
void NodeSkipList<Value, Key, numLevels>::clear(void)
{
    for (int i = 0; i < numLevels; ++i)
        Base::nextJump[i] = 0;

    Base::levelHighest = -1;
}

//------------------------------------------------------------------------------

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(void)
{
    clear();
}

//------------------------------------------------------------------------------

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(const Key& tkey)
{
    clear();

    Base::Base::key = tkey;
}

//------------------------------------------------------------------------------

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(const Key& tkey, const Value& val)
{
    clear();

    Base::Base::key = tkey;
    Base::Base::value = val;
}


//==============================================================================
// class SkipList
//==============================================================================

template <class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::SkipList(double probability)
{
    _probability = probability;

    // Lets use m_pPreHead as a final sentinel element
    for (int i = 0; i < numLevels; ++i)
        Base::_preHead->nextJump[i] = Base::_preHead;

    Base::_preHead->levelHighest = numLevels - 1;
}

template<class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::insert(const Value& val, const Key& key) {
    Node* node = this->_preHead;

    Node* update[this->_preHead->levelHighest+1];

    int lvl = this->_preHead->levelHighest;

    for (int i = lvl; i >= 0; --i) {
        while (node->nextJump[i]->key<=key and node->nextJump[i] != this->_preHead)
            node=node->nextJump[i];

        update[i] = node;
    }

    Node* insNode = new Node(key,val);
    insNode->next=update[0]->next;
    update[0]->next=insNode;

    lvl=0;
    //закинем ноду в верхние слои(или не закинем, тут уж как повезет)
    while (lvl<this->_preHead->levelHighest)
    {
        if ((double) rand() / (RAND_MAX) > _probability and lvl!=0 )
            break;


        insNode->nextJump[lvl]=update[lvl]->nextJump[lvl];
        update[lvl]->nextJump[lvl]=insNode;
        ++lvl;
    }

    insNode->levelHighest=lvl;
}

template<class Value, class Key, int numLevels>
void SkipList<Value, Key, numLevels>::removeNext(SkipList::Node* nodeBefore) {

    if (!nodeBefore || !nodeBefore->next || nodeBefore->next==this->_preHead)
       throw std::invalid_argument("");

    Node* node=this->_preHead;

    for (int i = nodeBefore->next->levelHighest; i >=0 ; --i)
    {
        node=this->_preHead;

       while (nodeBefore->nextJump[i]!=this->_preHead and node->nextJump[i]!=nodeBefore->next)
           node=node->nextJump[i];

            node->nextJump[i] = nodeBefore->next->nextJump[i];

    }

Node* todel = nodeBefore->next;
nodeBefore->next= nodeBefore->next->next;
delete todel;

}

template<class Value, class Key, int numLevels>
typename SkipList<Value, Key, numLevels>::Node* SkipList<Value, Key, numLevels>::findLastLessThan(const Key& key) const {

    if (this->_preHead->next == this->_preHead)
        return this->_preHead;

    Node* node = this->_preHead;
    int lvl = node->levelHighest;

    while (lvl>=0){
        while(node->nextJump[lvl]->key < key and node->nextJump[lvl] != this->_preHead)
            node = node->nextJump[lvl];

        --lvl;
    }

    while(node->next->key < key && node->next != this->_preHead)
        node = node->next;

    // If there is no node with the
    // defined key in the list
    return node;

}

template<class Value, class Key, int numLevels>
typename SkipList<Value, Key, numLevels>::Node* SkipList<Value, Key, numLevels>::findFirst(const Key& key) const {

    Node* node = this->_preHead;

    for (int i = this->_preHead->levelHighest; i >= 0; --i) {
        while (node->nextJump[i]->key<key and node->nextJump[i] != this->_preHead)
            node=node->nextJump[i];
    }

    while(node->next!=this->_preHead and node->next->key<key)
        node = node->next;

    if(node->next->key==key and node->next!=this->_preHead)
        return node->next;

    return nullptr;
}

template<class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::~SkipList() {

}
