#include <iostream>
#include "merge_sort.h"

using namespace std;
int main() {
    int numbers[] = {1};
    merge_sort(numbers, 1);
    for (int i = 0; i < 1; ++i) {
        cout << numbers[i] << " ";
    }
}