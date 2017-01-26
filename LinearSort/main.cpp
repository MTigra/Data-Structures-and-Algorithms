#include <iostream>
#include "LinearSort.h"
using namespace std;
int length(int number, int base){
    int count = 0;
    while(number != 0) {
        ++count;
        number /= base;
    }
    return count;
}
int main() {
    int A[] = {1, 4, -8, 3, 2, -1, 5, 5, -7, 9, -8, -1};
    counting_sort(A, 12);
    for (int i = 0; i < 12; ++i) {
        cout << A[i] << " ";
    }
    int B[] = {1011, 100, 101, 1100};
    sort_at_digit(B,4,2,1);
    cout << "\n";
    for (int i = 0; i < 4; ++i) {
        cout << B[i] << " ";
    }
    cout << "\n";
    int C[] = {1011,100,101,1100};
    radix_sort(C, 4, 2);
    for (int j = 0; j < 4; ++j) {
        cout << C[j] << " ";
    }
    cout << "\n";
    int D[] = {11, 4, 88, 3, 55, 11, -55, -56, 7, 9, 88, -111};
    radix_sort(D, 12, 10);
    for (int i = 0; i < 12; ++i) {
        cout << D[i] << " ";
    }
    cout << "\n";
    cout<< length(-24343, 10);
    return 0;
}