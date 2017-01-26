//
// Created by Nikita Marinosyan on 26.09.16.
//

#include "quick_sort.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
using namespace std;
int q_sort::get_middle_pivot(int from, int to) {

    return (to - 1 + from)/2;
}

int q_sort::get_last_pivot(int from, int to) {

    return to-1;
}

int q_sort::get_rand_pivot(int from, int to) {

    srand(time(NULL));
    return rand() % (to - from) + from;
}

int q_sort::rearrange_array_with_pivot(int *arr, int from, int to, int pivot_index) {

    int rearrangementIndex = from;
    // Remember the pivot value
    int pivot = arr[pivot_index];

    // Swap pivot and the last element
    swap(arr[pivot_index], arr[to - 1]);

    // Rearrange array
    for (int i = from; i < to; ++i) {
        if (arr[i] < pivot){
            swap(arr[i], arr[rearrangementIndex]);
            ++rearrangementIndex;
        }
    }

    // Move pivot to the proper place
    swap(arr[rearrangementIndex], arr[to - 1]);

    return rearrangementIndex;
}

void q_sort::quick_sort(int *arr, int from, int to, pivot_chooser pivotChooser) {

    if (from < to - 1) {

        // Get the pivot index
        int rearrangementIndex = rearrange_array_with_pivot(arr, from, to, pivotChooser(from, to));

        // Sort the left part of the array
        quick_sort(arr, from, rearrangementIndex, pivotChooser);

        //Sort the right part of the array
        quick_sort(arr, rearrangementIndex + 1, to, pivotChooser);
    }
}

void q_sort::quick_sort_last(int *arr, int n) {
    quick_sort(arr, 0, n, get_last_pivot);
}

void q_sort::quick_sort_middle(int *arr, int n) {
    quick_sort(arr, 0, n, get_middle_pivot);
}

void q_sort::quick_sort_rand(int *arr, int n) {
    quick_sort(arr, 0, n, get_rand_pivot);
}

