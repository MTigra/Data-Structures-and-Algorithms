////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Safearray class methods definition
/// \author    Nikita Marinosyan
/// \date      31.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// This file contains templates of the method of the class Safearray.
/// This file is not going to be used w/o its main counterpart, safearray.h.
/// Since the file is used only through safearray.h, which has its own "include 
/// watcher", we add no addition "watcher" here.
///
////////////////////////////////////////////////////////////////////////////////

// #ifndef    // No need to have a watcher here!


#include "safearray.h"


// we have to indicate that methods of the class Safearray are also inside the namespace xi
namespace xi {


    template<class T>
    SafeArray<T>::SafeArray(size_t cap) {
        // Allocate memory for the array
        _storage = new T[cap];

        // Set capacity
        _capacity = cap;
    }

    template <class T>
    SafeArray<T>::~SafeArray() {
        delete[] _storage;
        _storage = nullptr;
        _capacity = 0;
    }

    template <class T>
    size_t SafeArray<T>::getCapacity() const {
        return _capacity;
    }

    template <class T>
    T& SafeArray<T>::SafeArray(const SafeArray &obj) {

        // Copy array
        _storage = new SafeArray(obj._capacity);
        for (int i = 0; i < _capacity; ++i) {
            _storage[i] = obj[i];
        }

        // Set the proper capacity
        _capacity = obj._capacity;
    }

    template <class T>
    T& SafeArray::operator[](size_t k) {
        // Check if the index is in the array bounds
        checkBounds(k);

        return _storage[k];
    }

    template <class T>
    const T& SafeArray::operator[](size_t k) const {
        // Check if the index is in the array bounds
        checkBounds(k);


        return _storage[k];
    }

    template <class T>
    void SafeArray::checkBounds(size_t index) const {
        if (index > _capacity - 1) throw std::out_of_range("Index out of range!");
    }

} // namespace xi
