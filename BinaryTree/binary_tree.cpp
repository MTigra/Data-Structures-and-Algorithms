//
// Created by Nikita on 10.11.16.
//

#include "binary_tree.h"
#include <cstdlib>
#include <stdexcept>

using namespace std;

template<class T>
void BinaryTree<T>::insert(int key, T value) {
    // Check if the tree is empty
    if (head == nullptr) {
        // Add the first node to the tree
        head = new Node(key, value);

        // Increment tree size by one
        ++size;
    } else {
        // Tree is not empty
        // Search for the right place to insert new node
        Node *current_node = head;
        while (current_node != nullptr) {

            // Choose the subtree
            if (current_node->key > key) { // Go to the left subtree

                // Check if the left child is empty
                if (current_node->left == nullptr) {

                    // Insertion place is found
                    // and we need to add the node
                    current_node->left = new Node(key, value);

                    // Increment tree size by one
                    ++size;

                    // Break the loop
                    current_node = nullptr;
                } else {
                    // Go deeper in the tree
                    current_node = current_node->left;
                }
            } else if (current_node->key < key) { // Go to the right subtree

                // Check if the right child is empty
                if (current_node->right == nullptr) {

                    // Insertion place is found
                    // and we need to add the node
                    current_node->right = new Node(key, value);

                    // Increment tree size by one
                    ++size;

                    // Break the loop
                    current_node = nullptr;
                } else {
                    // Go deeper in the tree
                    current_node = current_node->right;
                }
            }
            else {
                throw logic_error("The key is already exists!");
            }
        }
    }
}

template <class T>
T BinaryTree<T>::find(int key) {

    // Pointer to the current node
    Node *current_node = head;

    // Search for the node with the defined key
    while (current_node != nullptr && current_node->key != key) {
        if (key < current_node->key) {
            // Since the key is smaller than current node key
            // we need to inspect the left child
            current_node = current_node->left;
        }
        else {
            // As there are not similar keys
            // it means the key is greater than current node key
            // so we need to inspect the right child
            current_node = current_node->right;
        }
    }

    // Check if the required node
    // has been found
    if (current_node != nullptr) {
        // Return the pointer of the node
        // on which the loop broke
        return current_node;
    }
    else throw logic_error("No node has been found!");
}

template <class T>
void BinaryTree<T>::remove(int key) {
    // Pointer to the current node
    Node* current_node = head;

    // Pointer to the parent node
    // of the current node
    Node* parent_node;

    // Make sure the tree is not empty
    if (current_node != nullptr) {

        // Do the search loop
        while (current_node != nullptr) {

            // Check if the current element
            // has the key we search for
            if (current_node->key == key) {

                // Check if the current node is leaf
                if (current_node->left == nullptr && current_node->right == nullptr) {

                    // Check if the current node has a parent
                    if (parent_node == nullptr) {
                        current_node = nullptr;
                    }
                    else {
                        // Find the parent and
                        // delete the child node
                        if (parent_node->right == current_node) {
                            parent_node->right = nullptr;
                        }
                        else {
                            parent_node->left = nullptr;
                        }
                        delete current_node;
                    }
                }

                // Check if the current node has both children
                else if (current_node->left != nullptr && current_node->right != nullptr) {
                    // Check if the current node has a parent
                    if (parent_node == nullptr) {
                        // Just remove it
                    }
                }
                // Decrement the size of the tree by one
                --size;
            }
        }
    }
}
