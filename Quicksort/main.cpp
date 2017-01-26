#include <iostream>
#include "quick_sort.h"

using namespace std;
int main() {
    int A[] = {7,2,1,6,8,5,3,4};
    int B[] = {7,2,1,6,8,5,3,4};
    int C[] = {7,2,1,6,8,5,3,4};
    q_sort::quick_sort_rand(A,8);
    for (int i = 0; i < 8; ++i) {
        cout << A[i];
    }
    cout << "\n";
    q_sort::quick_sort_last(A,8);
    for (int i = 0; i < 8; ++i) {
        cout << A[i];
    }
    cout << "\n";
    q_sort::quick_sort_middle(C,8);
    for (int i = 0; i < 8; ++i) {
        cout << C[i];
    }
    return 0;
}