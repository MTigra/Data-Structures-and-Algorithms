//
// Created by Nikita Marinosyan on 19.09.16.
//

#include "merge_sort.h"

void merge_sort(int *arr, int n) {
    divide_and_merge(arr, 0, n);
}

void merge(int *arr, int start_first, int start_second, int end) {

    // Temporary array which is used to store data
    // from the original array which makes possible
    // to apply changes to the original one
    int total = end - start_first;
    int* tmp = new int[total];
    for (int i = 0; i < total; ++i) {
        tmp[i] = arr[start_first + i];
    }

    int length1 = start_second - start_first;

    // Indices which are used to control the while cycle
    int i = 0, j = length1, k = start_first;

    // Compare the next pair from two parts which are being merged
    // and put the smallest number in the original array
    while (i < length1 && j < total){
        if(tmp[i] <= tmp[j]){
            arr[k] = tmp[i++];
        }
        else {
            arr[k] = tmp[j++];
        }
        ++k;
    }

    // Fill in the original array by adding
    // the remained elements
    while(i < length1) {
        arr[k] = tmp[i];
        ++k;
        ++i;
    }

    while(j < total) {
        arr[k] = tmp[j];
        ++k;
        ++j;
    }
}

void divide_and_merge(int *arr, int left, int right) {
    if(left < right-1) {
        int mid = (right - 1 + left) / 2;
        divide_and_merge(arr, left, mid+1);
        divide_and_merge(arr, mid+1, right);
        merge(arr, left, mid+1, right);
    }
}
