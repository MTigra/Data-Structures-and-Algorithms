////////////////////////////////////////////////////////////////////////////////
// Module Name:  xipoint.h/cpp
// Authors:      Sergey Shershakov, Nikita Marinosyan
// Date:         17.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "xipoint.h"
#include <cstdlib>
#include <algorithm>        // min

using namespace std;

namespace xi {

    // Implementation of Point class
    Point::Point(int x, int y) {
        _x = x;
        _y = y;
    }

    int Point::getY() const {
        return _y;
    }

    int Point::getX() const {
        return _x;
    }

    void Point::setY(int y) {
        _y = y;
    }

    void Point::setX(int x){
        _x = x;
    }

    void Point::shift(int xSh, int ySh) {
        _x += xSh;
        _y += ySh;
    }

    void Point::shift(const Point &pt) {
        _x += pt._x;
        _y += pt._y;
    }

    void Point::shift(int shf) {
        _x += shf;
        _y += shf;
    }

    // Implementation of PointArray class
    PointArray::PointArray() {
        _arr = nullptr;
        _size = 0;
    }

    PointArray::PointArray(const Point *points, const PointArray::Uint n) {
        _arr = new Point[n];
        _size = n;
        for (PointArray::Uint i = 0; i < n; ++i) {
            _arr[i] = points[i];
        }
    }

    PointArray::PointArray(const PointArray &pv){
        _arr = new Point[pv._size];
        _size = pv._size;
        for (PointArray::Uint i = 0; i < _size; ++i) {
            _arr[i] = *pv.get(i);
        }
    }

    PointArray::~PointArray() {
        clear();
    }

    void PointArray::clear() {
        delete[] _arr;
        _arr = nullptr;
        _size = 0;
    }

    const PointArray::Uint PointArray::getSize() const {
        return _size;
    }

    Point* PointArray::get(PointArray::Uint pos) {
        if (pos >= _size) return nullptr;
        return &_arr[pos];
    }

    const Point* PointArray::get(PointArray::Uint pos) const {
        if (pos >= _size) return nullptr;
        return &_arr[pos];
    }

    void PointArray::resize(PointArray::Uint n) {

        Point* _new = new Point[n];

        // Copy the min(n, _size) elements to the new array
        for (PointArray::Uint j = 0; j < min(n, _size); ++j) {
            _new[j] = _arr[j];
        }

        // Delete the current array
        clear();

        // Assign new array to the old one
        _arr = _new;

        // Change the size
        _size = n;

    }

    void PointArray::append(const Point &pt) {

        // Rearrange memory in order to
        // make place for the new element
        resize(_size + 1);

        // Assign the new element to the array
        _arr[_size - 1] = pt;
    }

    void PointArray::insert(const Point &pt, PointArray::Uint pos) {
        // Add element to the end if it is >= number of elements
        if (pos >= _size) append(pt);
        else {
            resize(_size + 1);
            for (int i = _size - 1; i > pos; --i) {
                _arr[i] = _arr[i - 1];
            }
            _arr[pos] = pt;
        }
    }

    void PointArray::remove(const PointArray::Uint pos) {

        // Check if there is an
        // element in defined position
        if (pos < _size) {

            // Shift the element which is required
            // to be removed to the end of the array
            for (PointArray::Uint i = pos; i < _size - 1; ++i) {
                _arr[i] = _arr[i + 1];
            }

            // Remove the last element
            resize(_size - 1);

            // Check if the array is empty now
            // and we need to delete it
            if (_size == 0) {
                clear();
            }
        }
    }

} // namespace xi {