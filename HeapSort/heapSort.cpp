//
// Created by Nikita Marinosyan on 04.10.16.
//

#include "heapSort.h"
#include <cstdlib>
#include <iostream>

using namespace std;

void Heap::heapifyDown(int index) {

    // Get parent and nodes indices
    int smallestValueIndex = index;
    int leftNode = 2 * index;
    int rightNode = 2 * index + 1;

    // Get the index of the min value
    if (leftNode < currentSize && storage[leftNode] < storage[smallestValueIndex]) {
        smallestValueIndex = leftNode;
    }
    if (rightNode < currentSize && storage[rightNode] < storage[smallestValueIndex]) {
        smallestValueIndex = rightNode;
    }

    // Swap current element with the its
    // minimal node if required
    if (smallestValueIndex != index) {

        swap(storage[index], storage[smallestValueIndex]);

        // Recursive call to make
        // further changes if needed
        heapifyDown(smallestValueIndex);
    }
}

void Heap::heapifyUp(int index){

    // Get parent index
    int parentIndex = index/2;

    // Swap current element with the its
    // parent if required
    if (parentIndex > 0 && storage[parentIndex] > storage[index]) {

        swap(storage[parentIndex], storage[index]);

        // Recursive call to make
        // further changes if needed
        heapifyUp(parentIndex);
    }
}

void Heap::insert(const int value) {

    // Check if there is enough space
    // in the array to insert the value
    if (currentSize <= capacity) {
        if (currentSize == 0) {
            storage[currentSize + 1] = value;
            currentSize = 2;
        } else {
            storage[currentSize] = value;
            heapifyUp(currentSize);
            ++currentSize;
        }
    }
    else {
            throw std::length_error("Couldn't insert element, because the heap is already full");
    }
}

int Heap::extractMin() {

    // Check if the heap has elements stored
    if(currentSize > 1) {
        // Remember the root value (min one)
        int min = getMin();

        // 'Swap' the first and the last elements
        storage[1] = storage[currentSize - 1];
        storage[currentSize - 1] = min;

        // Reduce the size of the heap
        --currentSize;

        // Change array to a proper state
        heapifyDown(1);
        return min;
    }
    else {
        throw std::length_error("Couldn't extract element, because the heap is empty");
    }
}

int Heap::getMin() {
    return storage[1];
}


Heap::Heap(const int *source, const int n) : capacity(n) {

    // Initialize fields
    currentSize = 0;
    storage = new int[n+1];

    // Insert elements in the storage array
    // in the correct order so they are
    // forming a heap
    for (int i = 0; i < n; ++i) {
        insert(source[i]);
    }
}

Heap::~Heap() {

    // Clear memory
    delete[] storage;
}

void Heapsort::heapSort(int *arr, int n) {
    Heap heap(arr, n);
    for (int i = 0; i < n; ++i) {
        arr[i] = heap.extractMin();
    }
}
