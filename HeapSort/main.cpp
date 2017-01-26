#include <iostream>
#include "heapSort.h"
#include <cstdlib>

using namespace std;
int main() {
    int A[] = {2,1,5,6,0,-1,-4,6,9};
    Heapsort::heapSort(A, 9);
    for (int i = 0; i < 9; ++i) {
      cout << A[i] << " ";
    }
}