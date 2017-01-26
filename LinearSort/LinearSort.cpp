//
// Created by Nikita Marinosyan on 15.09.16.
//

#include "LinearSort.h"
#include <Math.h>

void counting_sort(int *arr, int n) {

    //Find out max and min elements of the original array
    //to get length for array C
    int max = max_element(arr, n);
    int min = min_element(arr, n);

    //Create array for storing how many numbers
    //equal or less than current are left
    int* C = new int[max - min + 1];

    //Create array to store sorted numbers
    int* B = new int[n];

    for (int i = 0; i < max - min + 1; ++i) {
        C[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        ++C[arr[i] - min];
    }
    for (int i = 1; i < max - min + 1; ++i) {
        C[i] += C[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        C[arr[i] - min] = C[arr[i] - min] - 1;
        B[C[arr[i] - min]] = arr[i];
    }
    copy_array(B, arr, n);

    //Memory clear
    delete[] B;
    delete[] C;
}

/**
 * Utility method to get length
 * of the number with selected base
 */
int get_length(int number, int base){
    int count = 0;
    while(number != 0) {
        ++count;
        number /= base;
    }
    return count;
}

void radix_sort(int *arr, int n, int base) {
    int length = get_length(arr[0], base);
    for (int j = 1; j < n; ++j) {
        if(length < get_length(arr[j], base)) {
            length = get_length(arr[j], base);
        }
    }
    for (int i = 0; i < length; ++i) {
        sort_at_digit(arr, n, base, i);
    }
}

void sort_at_digit(int *arr, int n, int base, int digit_index) {

    int* A = new int[n];
    for (int j = 0; j < n; ++j) {
        A[j] = get_digit(arr[j], base, digit_index);
    }
    int max = max_element(A, n);
    int min = min_element(A,n);

    int* C = new int[max - min + 1];
    for (int i = 0; i < max - min + 1; ++i)
    {
        C[i] = 0;
    }
    for (int i = 0; i < n; ++i)
    {
        C[get_digit(arr[i], base, digit_index) - min] = C[get_digit(arr[i], base, digit_index) - min] + 1;
    }
    for (int i = 1; i < max - min + 1; ++i)
    {
        C[i] = C[i] + C[i - 1];
    }
    int* B = new int[n];
    for (int i = 0; i < n; ++i)
    {
        B[i] = 0;
    }
    for (int i = n - 1; i >= 0; --i)
    {
        B[C[get_digit(arr[i], base, digit_index) - min] - 1] = arr[i];
        C[get_digit(arr[i], base, digit_index) - min] = C[get_digit(arr[i], base, digit_index) - min] - 1;
    }
    copy_array(B, arr, n);
    delete[] C;
    delete[] B;
}

int get_digit(int number, int base, int digit_index) {
    return (number / (int)(pow(base, digit_index))) % base;
}

int max_element(int *arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; ++i) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int min_element(int *arr, int n) {
    int min = arr[0];
    for (int i = 1; i < n; ++i) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

void copy_array(int *from, int *to, int size) {
    for (int i = 0; i < size; ++i) {
        to[i] = from[i];
    }
}